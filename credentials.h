#define EVENTO_TELEGRAM "Msg_Telegram"
#define EVENTO_IFTTT "Push_Notif"
#define EVENTO_LINE "Msg_Line"
#define EVENTO_GMAIL "Msg_Gmail"
#define EVENTO_MESSENGER "Msg_Messenger"
#define EVENTO_GPS "Trigger_GPS"

#define HOSTIFTTT "maker.ifttt.com"
#define IFTTTKEY "PY2Ix8TTen8AVSHlBMDfF"
#define BOTtoken "772125081:AAG_rNNQwaKg6sKDMnqJtt6zXZoWh2TmEqg" //siberikece_bot
#define buzz D3
#define xpin A0
#define ledPin LED_BUILTIN
#define cekpin D5

const char ssid[] = "Naaey";     
const char password[] = "qwertyasdfgzxcvb";
const char auth[] = "46d00af14add4105a239323f95e4884f";
static int flag = 0; 
static float lat_, lng_;
static String lat_str, lng_str; 
static String buf = "http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
String wifi = "WiFi is connected to ";
String defaultChatId = "744657696";
String defaultChatId2 = "-390701710";
int cekpin_flag = 0;

//const char ssid[] = "NASA";     
//const char password[] = "AoEiuklsjbcv419514";
//const char ssid[] = "TMB 105";     
//const char password[] = "rumahkos105"; 
//const char ssid[] = "Hotspot";     
//const char password[] = "gakgawepassword";

//static String lat_str = "-7.273376", lng_str = "112.797868"; 
