/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "mono:size=10","Symbols Nerd Font:size=10" };
static const char normbordercolor[]       = "#3B4252";
static const char normbgcolor[]           = "#2E3440";
static const char normfgcolor[]           = "#D8DEE9";
static const char selbordercolor[]        = "#434C5E";
static const char selbgcolor[]            = "#434C5E";
static const char selfgcolor[]            = "#ECEFF4";

static const unsigned int baralpha = 140;
static const unsigned int borderalpha = OPAQUE;

static const char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel] =  { selfgcolor,  selbgcolor,  selbordercolor },
};


static const unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

static const char *const autostart[] = {
    "/home/kali/.config/dwm/startup.sh", NULL,
    NULL /* terminate */
};

/* tagging */
//static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = {"ένα","δύο","τρία", "τέσσερα", "πέντε", "έξι" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "Alacritty",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
#include "horizgrid.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "###",      horizgrid },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

// Includes
#include "movestack.c"
#include "shift-tools.c"
#include <X11/XF86keysym.h>
#include "unfloat.c"

/* commands */
static const char *rofi[] = { "rofi", "-show", "run", NULL };
static const char *wallscript[] = { "wallpaper_script.sh", NULL };
static const char *wallrandom[] = { "wallrandom.sh", NULL };
static const char *browser[] = { "librewolf", NULL };
static const char *printscr[] = { "flameshot", "gui", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *upvol[]      = { "/usr/bin/wpctl",   "set-volume", "@DEFAULT_AUDIO_SINK@",      "5%+",      NULL };
static const char *downvol[]    = { "/usr/bin/wpctl",   "set-volume", "@DEFAULT_AUDIO_SINK@",      "5%-",      NULL };
static const char *mutevol[]    = { "/usr/bin/wpctl",   "set-mute",   "@DEFAULT_AUDIO_SINK@",      "toggle",   NULL };
static const char *pctlpause[]  = { "playerctl", "play-pause", NULL };
static const char *pctlnext[]  = { "playerctl","next" , NULL };
static const char *pctlprevious[]  = { "playerctl", "previous", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = rofi} },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = wallscript} },
	{ MODKEY|ControlMask,           XK_w,      spawn,          {.v = wallrandom} },
	{ MODKEY,                       XK_w,      spawn,          {.v = browser} },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_e,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,	        	XK_h,      shiftboth,      { .i = -1 }	},
	{ MODKEY|ControlMask,	    	XK_h,      shiftswaptags,  { .i = -1 }	},
	{ MODKEY|ControlMask,		    XK_l,      shiftswaptags,  { .i = +1 }	},
	{ MODKEY|ShiftMask,             XK_l,      shiftboth,      { .i = +1 }	},
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_d,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                    XK_q,      killclient,     {0} },
    { MODKEY,                       XK_z,      unfloatvisible, {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,		    XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
    { MODKEY,                       XK_s, scratchpad_show, {.i = 1} },
    { MODKEY,                       XK_y, scratchpad_show, {.i = 2} },
    { MODKEY,                       XK_u, scratchpad_show, {.i = 3} },
    { MODKEY|ShiftMask,             XK_s, scratchpad_hide, {.i = 1} },
    { MODKEY|ShiftMask,             XK_y, scratchpad_hide, {.i = 2} },
    { MODKEY|ShiftMask,             XK_u, scratchpad_hide, {.i = 3} },
    { MODKEY|ShiftMask,             XK_r,      scratchpad_remove,           {0} },
	{ MODKEY,                       XK_o, shiftviewclients,    { .i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,	shiftview,         { .i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,	shiftview,         { .i = -1 } },
	{ MODKEY,	                    XK_i, shiftviewclients,    { .i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },	
	{ 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                       XF86XK_AudioMute, spawn, {.v = mutevol } },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
	{ 0,                       XF86XK_AudioPrev,      spawn,          {.v = pctlprevious} },
	{ 0,                       XF86XK_AudioNext,      spawn,          {.v = pctlnext} },
	{ 0,                       XF86XK_AudioPlay,      spawn,          {.v = pctlpause} },
	{ 0,	                        XK_Print,  spawn,          {.v = printscr} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

