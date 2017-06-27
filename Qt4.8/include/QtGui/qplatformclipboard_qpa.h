/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QPLATFORMCLIPBOARD_QPA_H
#define QPLATFORMCLIPBOARD_QPA_H

#include <qplatformdefs.h>

#ifndef QT_NO_CLIPBOARD

#include <QtGui/QClipboard>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

class Q_GUI_EXPORT QPlatformClipboard
{
public:
    virtual ~QPlatformClipboard();

    virtual QMimeData *mimeData(QClipboard::Mode mode = QClipboard::Clipboard);
    virtual void setMimeData(QMimeData *data, QClipboard::Mode mode = QClipboard::Clipboard);
    virtual bool supportsMode(QClipboard::Mode mode) const;
    void emitChanged(QClipboard::Mode mode);
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // QT_NO_CLIPBOARD

#endif //QPLATFORMCLIPBOARD_QPA_H