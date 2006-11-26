/*******************************************************************************

   Copyright (C) 2006 M.K.A. <wyrmchild@sourceforge.net>
   For more info, see: http://drawpile.sourceforge.net/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

*******************************************************************************/

#ifndef Protocol_Defaults_INCLUDED
#define Protocol_Defaults_INCLUDED

namespace protocol
{

//! Board identifier for no particular board (global) things. Mostly for Chat messages.
const uint8_t Global = 0;

/* only used by Identifier message */
const uint8_t identifier_size = 8;

//! No user identifier defined.
const uint8_t null_user = 255;

//! No protocol revision defined.
const uint16_t null_revision = 0x0000;

//! No feature implementation level defined.
const uint16_t null_implementation = 0x0000;

//! Protocol identifier string.
const char identifierString[identifier_size] = {'D','r','a','w','P','i','l','e'};

} // namespace protocol

#endif // Protocol_Defaults_INCLUDED