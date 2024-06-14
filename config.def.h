/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 4;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12", "Symbols Nerd Font:pixelsize=17:type=2048-em:antialias=true:autohint=true", "Source Han Serif CN:size=12"};
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#111111";  // 状态条底色
static const char col_gray2[]       = "#444444";  // 当static const unsigned int borderpx不为0时，非活动窗口外边框颜色
static const char col_gray3[]       = "#bbbbbb";  // 当前非活动的title字体颜色
static const char col_gray4[]       = "#eeeeee";  // 当前活动的title字体颜色
static const char col_cyan[]        = "#FF6EB4";  // title底色
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "󰉋", "", "", "󰻞", "" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "󰉨",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY1 Mod1Mask
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "rofi", "-show", "run" };
static const char *termcmd[]  = { "xfce4-terminal", NULL };

static const Key keys[] = {
	/* modifier						key				function				argument */
	{ MODKEY1,						XK_space,		spawn,					{.v = roficmd } },				// 打开rofi程序启动器
	{ MODKEY1,						XK_Return,		spawn,					{.v = termcmd } },				// 打开终端
	{ MODKEY1,						XK_p,   		spawn,					SHCMD("flameshot gui") },		// 打开flameshot截图
	{ MODKEY,						XK_b,			togglebar,				{0} },							// 显示和隐藏bar
	{ MODKEY,						XK_j,			focusstack,				{.i = +1 } },					// 向左/上移动焦点
	{ MODKEY,						XK_k,			focusstack,				{.i = -1 } },					// 向右/下移动焦点
	{ MODKEY,						XK_h,			setmfact,				{.f = -0.05} },					// 窗口大小向左调整
	{ MODKEY,						XK_l,			setmfact,				{.f = +0.05} },					// 窗口大小向右调整
	{ MODKEY,						XK_i,			incnmaster,				{.i = +1 } },					// 窗口水平排列
	{ MODKEY,						XK_d,			incnmaster,				{.i = -1 } },					// 窗口竖直排列
	{ MODKEY,						XK_s,			zoom,					{0} },							// 对调两个窗口
	{ MODKEY1,						XK_Tab,			view,					{0} },							// 在最近使用的两个窗口间跳转查看，类似于windows的Ait+tab
	{ MODKEY,						XK_q,			killclient,				{0} },							// 关闭窗口
	{ MODKEY,						XK_t,			setlayout,				{.v = &layouts[0]} },			// 平铺模式
	{ MODKEY,						XK_f,			setlayout,				{.v = &layouts[1]} },			// 浮动模式
	{ MODKEY,						XK_m,			setlayout,				{.v = &layouts[2]} },			// 单页模式
	{ MODKEY,						XK_space,		setlayout,				{0} },							// 在平铺和浮动模式之间切换
	{ MODKEY|ShiftMask,				XK_space,		togglefloating,			{0} },							// 使窗口在平铺和浮动模式之间切换
	// { MODKEY,						XK_0,      view,					{.ui = ~0 } },					// 将所有打开的窗口在所有tag上显示
	// { MODKEY|ShiftMask,				XK_0,      tag,						{.ui = ~0 } },					// 将所有窗口显示在对应的tag上
	{ MODKEY,						XK_comma,		focusmon,				{.i = -1 } },					// super + 逗号 将焦点切换到前一个监视器
	{ MODKEY,						XK_period,		focusmon,				{.i = +1 } },					// super + 句号 将焦点切换到后一个监视器
	{ MODKEY|ShiftMask,				XK_comma,		tagmon,					{.i = -1 } },					// super + shift + 逗号 将当前选中的窗口移动到前一个标记的监视器
	{ MODKEY|ShiftMask,				XK_period,		tagmon,					{.i = +1 } },					// super + shift + 句号 将当前选中的窗口移动到后一个标记的监视器
	{ MODKEY,						XK_minus,		setgaps,				{.i = -1 } },					// super + 减号 减小gaps
	{ MODKEY,						XK_equal,		setgaps,				{.i = +1 } },					// super + 加号 增大gaps
	{ MODKEY|ShiftMask,				XK_equal,		setgaps,				{.i = 0  } },					// super + shift + 等号 关闭gaps
	{ MODKEY|ShiftMask,				XK_e,			quit,					{0} },							// 退出dwm

	TAGKEYS(                        XK_1,                      0)
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

