#include <portable.h>
#include <psos.h>
#include <string.h>
#include "genrlmsg.h"
#include "ipscdmsg.h"
#include "command.h"
#include "menu.h"
#include "preset.h"
#include "ascii.h"
#include "serial.h"

/* inbound messages to the mich queue */
typedef union{
  GENERIC_MSG     generic;
  HOST_COMMAND_MSG host_cmd;
} MSG_QUEUE_TYPE;

#define MAX_PASSWORD_LENGTH 20

// this is a random guess...
#define MAX_VGA_OBJECTS 40

#define VGACMD_GET_SCREEN_DATA_USING_PASSWORD      2001

extern MENU TheMainMenu[];

extern const SINT32 SecurityLevel;
extern const UINT32 HWConfiguration;
extern const UINT32 SWConfiguration;
extern CONFIGSETUP CurrentSetup;
extern SETUPS_Ver800 CurrentPreset;

static const STR * MainMenuPassword = "MAINMENU";

static UINT8 CommBuffer[4096];
static UINT16 CommBufLen;

// static const VGARECT StatusBarBackground = {};
// static const VGABUTTON StatusBarWeldResults = {};
// static const VGABUTTON StatusBarMainMenu = {};
// static const VGABUTTON StatusBarWeldSetup = {};
// static const VGABUTTON StatusBarGraphs = {};

static MENU local[MAX_VGA_OBJECTS];
static UINT8 count;

static STR LineBuf[21];

static void SelectScreenObjects(MENU * ScreenData)
{
   BOOLEAN TitleSeen;
   UINT8 i;
   TITLE * menu1;
   BOOLEAN SkipFlag;

   TitleSeen = FALSE;
   count = 0;
   for (i = 0; ScreenData[i].type != ENDLIST; i++)
   {
      SkipFlag = FALSE;
      switch (ScreenData[i].type)
      {
      case _TITLE :
      case _SUBMENU :         // the layout of first fields is exactlr same as in TITLE
         menu1 = (TITLE *) ScreenData[i].ptr;
         if (CurrentSetup.ControlLevel < menu1->CtrlLevel) SkipFlag = TRUE;
            else if (!(menu1->act & CurrentSetup.Actuator)) SkipFlag = TRUE;
            else if ((CurrentPreset.WeldMode != (menu1->mode & CurrentPreset.WeldMode)) &&
                    (menu1->mode != ALLMODES)) SkipFlag = TRUE;
            else if ((menu1->Mask1!=0)  && ((menu1->Mask1 & menu1->Cond1)!= (HWConfiguration & menu1->Mask1)))
                    SkipFlag = TRUE;
            else if ((menu1->Mask2!=0)  && ((menu1->Mask2 & menu1->Cond2)!= (SWConfiguration & menu1->Mask2)))
                    SkipFlag = TRUE;
            else if ((menu1->EnableFlag == TRUE) && (*menu1->Eptr == FALSE)) SkipFlag = TRUE;
            else if (menu1->level > SecurityLevel) SkipFlag = TRUE;
         break;
      default :
         SkipFlag = TRUE;
      }
      if (SkipFlag == FALSE)
      {
         local[count].ptr = ScreenData[i].ptr;
         local[count].type = ScreenData[i].type;
         count++;
         if (ScreenData[i].type == _TITLE)
            TitleSeen = TRUE;
      }
   }
/*
// this adds the status bar to all menus with title...
   if (TitleSeen)
   {
      local[count].ptr = &StatusBarBackground;
      local[count].type = _VGARECT;
      count++;
      local[count].ptr = &StatusBarWeldResults;
      local[count].type = _VGABUTTON;
      count++;
      local[count].ptr = &StatusBarMainMenu;
      local[count].type = _VGABUTTON;
      count++;
      local[count].ptr = &StatusBarWeldSetup;
      local[count].type = _VGABUTTON;
      count++;
      local[count].ptr = &StatusBarGraphs;
      local[count].type = _VGABUTTON;
      count++;
   }
*/
}

static void AddTitle(UINT8 Language, TITLE * Title)
{
   STR * ptr;
   CommBuffer[CommBufLen++] = _TITLE;
   strcpy(LineBuf, Title->Tptr[Language]);
   // Remove trailing blanks
   ptr = strchr(LineBuf, '\0') - 1;
   while ((*ptr == ' ') && (ptr != LineBuf))
      *ptr-- = '\0';
   CommBuffer[CommBufLen++] = strlen(LineBuf);
   strcpy((STR *) &CommBuffer[CommBufLen], LineBuf);
   CommBufLen += strlen(LineBuf);
}

static void AddSubmenu(UINT8 Language, SUBMENU * Submenu)
{
   STR * ptr;
   CommBuffer[CommBufLen++] = _SUBMENU;
   strcpy(LineBuf, Submenu->Tptr[Language]);
   // Remove trailing blanks
   ptr = strchr(LineBuf, '\0') - 1;
   while ((*ptr == ' ') && (ptr != LineBuf))
      *ptr-- = '\0';
   CommBuffer[CommBufLen++] = strlen(LineBuf);
   strcpy((STR *) &CommBuffer[CommBufLen], LineBuf);
   CommBufLen += strlen(LineBuf);
   memcpy(&CommBuffer[CommBufLen], &Submenu->Mptr, sizeof(MENU *));
   CommBufLen += sizeof(MENU *);
}

static void BuildScreen(UINT8 Language)
{
   UINT8 i;

   CommBufLen = 0;
   if (Language <= 4)
      CommBuffer[CommBufLen++] = 1;
   else
      CommBuffer[CommBufLen++] = 2;
   CommBuffer[CommBufLen++] = count;
   for (i = 0; i < count; i++)
   {
      switch (local[i].type)
      {
      case _TITLE :
         AddTitle(Language, (TITLE *) local[i].ptr);
         break;

      case _SUBMENU :
         AddSubmenu(Language, (SUBMENU *) local[i].ptr);
         break;

      default :
         break;
      }
   }
}

static UINT16 CreateAck(UINT8 * AckBuf, UINT16 Function, UINT8 * response, UINT16 len)
{
   UINT16 i, j;
	
   i = 0;
   AckBuf[i++] = ACK;
   AckBuf[i++] = DLE;
   AckBuf[i++] = STX;
   /* Increment index over byte count */
   i += 2;
   /* fill in function */
   AckBuf[i++] = (UINT8)(Function >> 8);
   AckBuf[i++] = (UINT8)Function;
   /* fill in the data */
   memcpy(&AckBuf[i], response, len);
   i += len;
   /* fill in byte count */
   AckBuf[3] = (UINT8)((i-3)>>8);
   AckBuf[4] = (UINT8) (i-3);   
   /* compute checksum */
   AckBuf[i] = 0;
   for (j=3; j<i; j++)
      AckBuf[i] ^= AckBuf[j];
   i++;
   /* add DLE, ETX to message */
   AckBuf[i++] = DLE;
   AckBuf[i++] = ETX;
   return i;
}

static void TransmitAck(UINT16 Function, UINT8 * Buffer, UINT16 Length)
{
   static UINT8 AckBuf[4096 + 16];
   UINT16 len;

   len = CreateAck(AckBuf, Function, Buffer, Length);
   SerialMessageQueue(AckBuf, len);   
}

static void TransmitNak(UINT16 Function)
{
   static UINT8 NakBuf[20];
   UINT8 i;
   UINT8 ch;
   UINT8 checksum = 0x00;

   i = 0;
   NakBuf[i++] = NAK;
   NakBuf[i++] = DLE;
   NakBuf[i++] = STX;

   ch = 0x00;
   checksum ^= ch;
   NakBuf[i++] = ch;
   ch = 0x04;
   checksum ^= ch;
   NakBuf[i++] = ch;

   ch = Function >> 8;
   checksum ^= ch;
   NakBuf[i++] = ch;

   ch = Function & 0xFF;
   checksum ^= ch;
   NakBuf[i++] = ch;

   NakBuf[i++] = checksum;
   NakBuf[i++] = DLE;
   NakBuf[i++] = ETX;

   SerialMessageQueue(NakBuf, i);
}

static void TransmitScreen(UINT16 Function, UINT8 Language, MENU * ScreenData)
{
   UINT8 i;
   SelectScreenObjects(ScreenData);
   BuildScreen(Language);
   TransmitAck(Function, CommBuffer, CommBufLen);
}

static void BuildMenuWithPassword(UINT16 CommandCount, UINT8 * Data)
{
   STR * Password;
   UINT8 Language;
   UINT8 PassLength;
   STR PasswordBuf[MAX_PASSWORD_LENGTH + 1]; // for '\0'

   // For now we'll ignore languages...
   Language = *Data++;
   PassLength = *Data++;
   // Bad password - early exit
   if (PassLength > MAX_PASSWORD_LENGTH)
   {
      TransmitNak(VGACMD_GET_SCREEN_DATA_USING_PASSWORD);
      return;
   }
   strncpy(PasswordBuf, (STR *) Data, PassLength);
   PasswordBuf[PassLength] = 0;
   if (strcmp(MainMenuPassword, (STR *) Data) == 0)
      TransmitScreen(VGACMD_GET_SCREEN_DATA_USING_PASSWORD, Language, TheMainMenu);
   else
      TransmitNak(VGACMD_GET_SCREEN_DATA_USING_PASSWORD);
}

static UINT16 CreateACK(UINT8 * AckBuf, UINT16 Function, UINT8 * response, UINT16 len)
{
	UINT16 i, j;
	
	i = 0;
	AckBuf[i++] = ACK;
	AckBuf[i++] = DLE;
	AckBuf[i++] = STX;
	/* Increment index over byte count */
	i += 2;
	/* fill in function */
	AckBuf[i++] = (UINT8)(Function >> 8);
	AckBuf[i++] = (UINT8)Function;
	/* fill in the data */
	memcpy(&AckBuf[i], response, len);
	i += len;
	/* fill in byte count */
	AckBuf[3] = (UINT8)((i-3)>>8);
	AckBuf[4] = (UINT8) (i-3);   
	/* compute checksum */
	AckBuf[i] = 0;
	for (j=3; j<i; j++)
		AckBuf[i] ^= AckBuf[j];
	i++;
	/* add DLE, ETX to message */
	AckBuf[i++] = DLE;
	AckBuf[i++] = ETX;

	return i;
}

BOOLEAN ProcessVgaHostCommand(GENERIC_MSG * msg)
{
   UINT16 CommandCount;
   UINT16 Function;
   HOST_COMMAND_MSG * HostCommand;
   UINT8 * Data;

   HostCommand = (HOST_COMMAND_MSG *) msg;
   CommandCount = HostCommand->byte_count + 9;
   Function = msg->common.opcode;
   Data = (UINT8 *) HostCommand->data_pointer;
   switch (Function)
   {
   case VGACMD_GET_SCREEN_DATA_USING_PASSWORD :
      BuildMenuWithPassword(CommandCount, Data);
      break;
   default :
      return FALSE;
   }
   return TRUE;
}
