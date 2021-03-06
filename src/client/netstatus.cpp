/*
   DrawPile - a collaborative drawing program.

   Copyright (C) 2006-2008 Calle Laakkonen

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
*/

#include <QAction>
#include <QLabel>
#include <QApplication>
#include <QClipboard>
#include <QHBoxLayout>

#include "sessioninfo.h"
#include "netstatus.h"
#include "popupmessage.h"
#include "icons.h"

namespace widgets {

NetStatus::NetStatus(QWidget *parent)
	: QWidget(parent)
{
	setMinimumHeight(16+2);

	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->setMargin(1);
	layout->setSpacing(4);

	// Host address label
	label_ = new QLabel(tr("not connected"), this);
	label_->setTextInteractionFlags(
			Qt::TextSelectableByMouse|Qt::TextSelectableByKeyboard
			);
	label_->setCursor(Qt::IBeamCursor);
	layout->addWidget(label_);

	// Action to copy address to clipboard
	copyaction_ = new QAction(tr("Copy address to clipboard"), this);
	copyaction_->setEnabled(false);
	label_->addAction(copyaction_);
	label_->setContextMenuPolicy(Qt::ActionsContextMenu);
	connect(copyaction_,SIGNAL(triggered()),this,SLOT(copyAddress()));

	// Network connection status icon
	icon_ = new QLabel(QString(), this);
	icon_->setPixmap(icon::network().pixmap(16,QIcon::Normal,QIcon::Off));
	icon_->setFixedSize(icon::network().actualSize(QSize(16,16)));
	layout->addWidget(icon_);

	// Popup label
	popup_ = new PopupMessage(this);
}

/**
 * Set the label to display the address.
 * A context menu to copy the address to clipboard will be enabled.
 * @param address the address to display
 */
void NetStatus::connectHost(const QString& address)
{
	address_ = address;
	label_->setText(tr("Host: %1").arg(address_));
	icon_->setPixmap(icon::network().pixmap(16,QIcon::Normal,QIcon::On));
	copyaction_->setEnabled(true);
	message(tr("Connected to %1").arg(address_));
}

/**
 * Set the label to indicate a lack of connection.
 * Context menu will be disabled.
 */
void NetStatus::disconnectHost()
{
	address_ = QString();
	label_->setText(tr("not connected"));
	icon_->setPixmap(icon::network().pixmap(16,QIcon::Normal,QIcon::Off));
	copyaction_->setEnabled(false);
	message(tr("Disconnected"));
}

/**
 * Copy the current address to clipboard.
 * Should not be called if disconnected.
 */
void NetStatus::copyAddress()
{
	QApplication::clipboard()->setText(address_);
	// Put address also in selection buffer so it can be pasted with
	// a middle mouse click where supported.
	QApplication::clipboard()->setText(address_, QClipboard::Selection);
}

void NetStatus::join(const network::User& user)
{
	message(tr("<b>%1</b> has joined").arg(user.name()));
}

void NetStatus::leave(const network::User& user)
{
	message(tr("<b>%1</b> has left").arg(user.name()));
}

void NetStatus::kicked(const network::User& user)
{
	message(tr("<b>%1</b> was kicked by session owner").arg(user.name()));
}

void NetStatus::lock(const QString& reason)
{
	message(tr("Board locked (%1)").arg(reason));
}

void NetStatus::unlock()
{
	message(tr("Board unlocked"));
}

void NetStatus::message(const QString& msg)
{
	popup_->setMessage(msg);
	popup_->popupAt(mapToGlobal(icon_->pos() +
				QPoint(icon_->width()/2, icon_->height()/2)));
	emit statusMessage(msg);
}

}

