//===============================================================================
//
//   File : libkvicodetester.cpp
//   Creation date : Mon 23 Dec 2002 20:23:59 2002 GMT by Szymon Stefanek
//
//   This toolbar is part of the KVirc irc client distribution
//   Copyright (C) 2002-2005 Szymon Stefanek (pragma at kvirc dot net)
//
//   This program is FREE software. You can redistribute it and/or
//   modify it under the terms of the GNU General Public License
//   as published by the Free Software Foundation; either version 2
//   of the License, or (at your opinion) any later version.
//
//   This program is distributed in the HOPE that it will be USEFUL,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program. If not, write to the Free Software Foundation,
//   Inc. ,59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
//===============================================================================

#include "codetester.h"

#include "kvi_module.h"
#include "kvi_locale.h"
#include "kvi_frame.h"
#include "kvi_pointerlist.h"


KviPointerList<KviCodeTesterWindow> * g_pCodeTesterWindowList = 0;


/*
	@doc: codetester.open
	@type:
		command
	@title:
		codetester.open
	@short:
		Shows the code tester window
	@syntax:
		codetester.open
	@description:
		Opens a new code tester window
*/

static bool codetester_kvs_cmd_open(KviKvsModuleCommandCall * c)
{
	KviCodeTesterWindow * w = new KviCodeTesterWindow(c->window()->frame());
	c->window()->frame()->addWindow(w);
	w->setFocus();
	return true;
}

static bool codetester_module_init(KviModule * m)
{
	KVSM_REGISTER_SIMPLE_COMMAND(m,"open",codetester_kvs_cmd_open);

	g_pCodeTesterWindowList = new KviPointerList<KviCodeTesterWindow>();
	g_pCodeTesterWindowList->setAutoDelete(false);
	return true;
}

static bool codetester_module_can_unload(KviModule * m)
{
	return (g_pCodeTesterWindowList->count() == 0);
}

static bool codetester_module_cleanup(KviModule *m)
{
	while(KviCodeTesterWindow * w = g_pCodeTesterWindowList->first())
	{
		w->close(); // deleted path!
	}
	return true;
}

KVIRC_MODULE(
	"CodeTester",                                                 // module name
	"4.0.0",                                                // module version
	"Copyright (C) 2002 Szymon Stefanek (pragma at kvirc dot net)", // author & (C)
	"Code tester window",
	codetester_module_init,
	codetester_module_can_unload,
	0,
	codetester_module_cleanup
)
