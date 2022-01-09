
#ifdef AUTOCONNECT_MENULABEL_HOME
#undef AUTOCONNECT_MENULABEL_HOME
#define AUTOCONNECT_MENULABEL_HOME   "Settings"
#endif

#ifdef AUTOCONNECT_URI
#undef AUTOCONNECT_URI
#define AUTOCONNECT_URI   "/wifi" 
#endif


/**< Override the hardcoded strings contained in the AutoConnect pages.    */
/**< e.g. for PlatformIO, you can add your environment in platformio.ini   */
/**< along with AC_LABLES macro which specifies the user-defined label     */
/**< constants as follows:                                                 */
/**<                                                                       */
/**< build_flags =                                                         */
/**<   -DAC_LABELS='"${PROJECT_SRC_DIR}/mylabels.h"'                       */
/**<                                                                       */
/**< And places mylabels.h, it needs a structure of the define directive   */
/**< provided per label string definition for the change your wants.       */
/**<                                                                       */
/**< #ifdef [ID YOU WANT TO CHANGE]                                        */
/**< #undef [ID YOU WANT TO CHANGE]                                        */
/**< #define [ID YOU WANT TO CHANGE] "NEW_STRING_FOR_THISONE"              */
/**< #endif                                                                */
/**<                                                                       */
/**< example:
#ifdef AUTOCONNECT_MENULABEL_CONFIGNEW
#undef AUTOCONNECT_MENULABEL_CONFIGNEW
#define AUTOCONNECT_MENULABEL_CONFIGNEW   "NEW_STRING_FOR_THISONE"
#endif
*/
