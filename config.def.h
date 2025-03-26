#define SESSION_FILE "/tmp/dwm-session"
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* fonts */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";

/* colors */
static const char sel_tag_col[]           = "#222222";
static const char text_col[]              = "#bbbbbb";
static const char sel_text_col[]          = "#eeeeee";
static const char col_cyan[]        	  = "#005577";
static const char bg_col[]        	  = "#000000";
static const char border_col[]        	  = "#000000";
static const char sel_border_col[]        = "#444444";
static const char *colors[][3]      = {
	/*                  fg           bg           border   */
	[SchemeNorm] = { text_col,     bg_col, 	     border_col },
	[SchemeSel]  = { sel_text_col, sel_tag_col,  sel_border_col  },
};

/* media keys */
static const char *upvol[] = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *light_up[]   = { "brightnessctl",   "set", "5%+", NULL };
static const char *light_down[] = { "brightnessctl",   "set", "5&-", NULL };

/* tags */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
       /* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
       { "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
       { NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */

};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "->",      tile },    /* first entry is default */
	{ "~",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask //set MODKEY to alt key
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },


/* commands */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenu_run"};
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, //spawns dmenu
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } }, //spawns terminal
	{ MODKEY,                       XK_b,      togglebar,      {0} }, //toggle the bar
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } }, //switches stack focus down
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } }, //switches stack focus up
	{ MODKEY|ControlMask,           XK_Left,   setmfact,       {.f = -0.05} }, //increase window size left
	{ MODKEY|ControlMask,           XK_Right,  setmfact,       {.f = +0.05} }, //increase window size right
	{ MODKEY,                       XK_Tab,    view,           {0} },//switch between last two tags
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} }, //kills window
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, //sets master stack layout
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, //sets float layout
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, //sets monocle layout
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } }, //decrese gaps
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } }, //increase gaps
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } }, //reset gaps to zero
	{ MODKEY|ShiftMask,             XK_q,      quit,           {1} }, //reset dwm
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} }, //kill dwm
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } }, //increase volume
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = downvol   } }, //decrease volume
	{ 0,                       XF86XK_AudioMute, 	    spawn, {.v = mutevol } }, //mute volume
	{ 0,		 	   XF86XK_MonBrightnessUp,  spawn, {.v = light_up} }, //increase brightness
	{ 0,			   XF86XK_MonBrightnessDown,spawn, {.v = light_down} }, //decrease brightness
	TAGKEYS(                        XK_1,                      0) //tags 1 through 9
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkClientWin,            MODKEY|ShiftMask,      Button1, togglefloating, {0} }, //toggle floating using modkey+shift+MB1
};
