/**
*  Copyright (C) 2017 3D Repo Ltd
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU Affero General Public License as
*  published by the Free Software Foundation, either version 3 of the
*  License, or (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Affero General Public License for more details.
*
*  You should have received a copy of the GNU Affero General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.1
import QtQuick.Controls.Material 2.1

import repo 1.0

Dialog {
    id: repoLoginDialog
    title: "Sign in"
    x: Math.round((window.width - width) / 2)
    y: Math.round(window.height / 6)
    width: Math.round(Math.min(window.width, window.height) / 3 * 2)
    modal: true
    focus: true

    standardButtons: Dialog.Ok | Dialog.Cancel
    onAccepted: {
        networkAccessManager.authenticate(username.text, password.text)
    }
    onRejected: {
        repoLoginDialog.close()
    }

    contentItem: ColumnLayout {
        spacing: 20

        Image {
            fillMode: Image.Pad
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            source: "image://materialicons/accountCircle/#FFcccccc"
            sourceSize.width: 200
            sourceSize.height: 200
            Layout.fillWidth: true
        }

        TextField {
            id: username
            placeholderText: qsTr("Username")
            Layout.fillWidth: true
        }

        TextField {
            id: password
            placeholderText: qsTr("Password")
            echoMode: TextInput.Password
            Layout.fillWidth: true
        }

        Label {
            text: networkAccessManager.lastErrorMessage
            color: Material.accent
//            opacity: (text.length != 0) ? 1.0 : 0.0
            horizontalAlignment: Label.AlignHCenter
            verticalAlignment: Label.AlignVCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
