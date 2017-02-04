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

#include "repo_csv_parser.h"

const QString repo::RepoCSVParser::delimiter = ";";

repo::RepoCSVParser::RepoCSVParser(QObject *parent)
    : QObject(parent)
{}

QVariantList repo::RepoCSVParser::parseCSV(const QString &filepath)
{
    QVariantList assets;
    QFile file(filepath);
    file.open(QIODevice::ReadOnly);
    QTextStream textStream(&file);

    QStringList header = textStream.readLine().split(delimiter);

    while (!textStream.atEnd())
    {
        QStringList line = textStream.readLine().split(delimiter);
        RepoAsset asset;
        for (int i = 0; i < header.size() && i < line.size(); ++i)
        {
            asset.insert(header.at(i), line.at(i));
        }

        if (!asset.tagCode().isEmpty())
            assets.append(asset);
    }
    file.close();
    return assets;
}
