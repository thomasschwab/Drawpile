/*
   DrawPile - a collaborative drawing program.

   Copyright (C) 2007 Calle Laakkonen

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
#include <QDebug>
#include <QHostInfo>
#include "localserver.h"

LocalServer::LocalServer()
	: port_(-1)
{
	server_.setProcessChannelMode(QProcess::MergedChannels);
}

LocalServer::~LocalServer()
{
	shutdown();
}

/**
 * @return the global LocalServer instance
 */
LocalServer *LocalServer::getInstance()
{
	static LocalServer *server = new LocalServer;
	return server;
}

/**
 * Attempt to discover the address most likely reachable from the
 * outside.
 * @return server hostname
 */
QString LocalServer::address()
{
	// TODO, does this work well enough?
	// other option would be to use QNetworkInterface
	return QHostInfo::localHostName();
}

/**
 * Start the server if it is not already running on the specified port.
 * @param port server listening port
 * @retval false if server could not be started
 * @post if returned true, server is now running in the background
 */
bool LocalServer::ensureRunning(int port)
{
	if(port_ != port)
		shutdown();
	if(server_.state()==QProcess::NotRunning) {
		QStringList args;
		args.append("-p " + QString::number(port));
		noerror_ = true;
		qDebug() << "starting server on port" << port;
		server_.start("drawpile-srv", args);
		if(server_.waitForStarted()==false) {
			qDebug() << "Failed to start server!";
			noerror_ = false;
			return false;
		}
		if(server_.waitForFinished(100)==true) {
			qDebug() << "Server exited just after starting!";
			qDebug() << serverOutput();
			return false;
		}
		qDebug() << "Started server, PID" << server_.pid();
		port_ = port;
	}
	return true;
}

/**
 * Get whatever the server has printed to its stdout and stderr.
 * @return server output
 */
QString LocalServer::serverOutput()
{
	return server_.readAll();
}

/**
 * @return error explanation
 */
QString LocalServer::errorString() const
{
	if(noerror_)
		return tr("Server exited with errors");
	switch(server_.error()) {
		case QProcess::FailedToStart:
			return tr("Couldn't start the server. Make sure it has been installed properly");
		case QProcess::Crashed:
			return tr("Server crashed on startup");
		case QProcess::Timedout:
			return tr("Server is taking too long to start");
		default: break;
	}
	return tr("Unexpected server error");
}

/**
 * Terminate the server
 * @post server is shut down
 */
void LocalServer::shutdown()
{
	if(server_.state() != QProcess::NotRunning) {
		server_.terminate();
		if(server_.waitForFinished() == false)
			server_.kill();
		server_.waitForFinished();
	}
}
