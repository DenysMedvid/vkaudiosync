/*
  *  VKAudioSync
  *  Copyright (C) 2011 Denis Medved <thebucefal@gmail.com>
  *
  *  This program is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "audiolistmodel.h"

AudioListModel::AudioListModel(QObject *parent) :
	QAbstractListModel(parent)
{
	m_pItems = new QList<AudioItem>;
}

AudioListModel::~AudioListModel()
{
	delete m_pItems;
}

int AudioListModel::rowCount(const QModelIndex &/*parent = QModelIndex()*/) const
{
	if (!m_pItems->empty()) {
		return m_pItems->size();
	}
	return 0;
}

QVariant AudioListModel::data(const QModelIndex &index, int role ) const
{
	int row = index.row();

	switch (role)
	{
	case AudioListModel::ROLE_ARTIST:
		return m_pItems->at(row).artist();

	case AudioListModel::ROLE_TITLE:
		return  m_pItems->at(row).title();

	case AudioListModel::ROLE_DURATION:
		return m_pItems->at(row).duration();

	case AudioListModel::ROLE_STATUS:
		return m_pItems->at(row).status();

	case AudioListModel::ROLE_PROGRESS:
		return m_pItems->at(row).progress();
	case AudioListModel::ROLE_URL:
		return m_pItems->at(row).url();

	default:
		return QVariant();
	}
}

bool AudioListModel::setData ( const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/)
{
	QList<AudioItem>::iterator iterator = m_pItems->begin();
	AudioItem* pitem;
	iterator += index.row();

	switch(role) {
	case AudioListModel::ROLE_PROGRESS:
		iterator->setProgress(value.toInt());
		if (iterator->progress() >= 100) {
			iterator->setStatus(AudioItem::STATUS_SYNCHRONIZED);
		}
		break;

	default:
		break;
	}

	emit dataChanged(index,index);

	return true;
}

void AudioListModel::resetStatuses()
{
	QList<AudioItem>::iterator iterator;
	AudioItem* pitem;

	for (iterator = m_pItems->begin(); iterator != m_pItems->end(); ++iterator) {
		iterator->setStatus(AudioItem::STATUS_UNDEFINED);
	}
	unsigned int count = m_pItems->size();

	if (count > 0)
		emit dataChanged(index(0),index(count-1));

}

void AudioListModel::parseXml(const QByteArray &xml)
{
	QString aid;
	QString owner;
	QString artist;
	QString title;
	QUrl url;
	unsigned int duration;
	AudioItem item;
	QDomDocument dom;
	dom.setContent(xml);
	QDomElement root = dom.firstChildElement(); // <response> root element

	clear();

	if (root.nodeName() == "response") {
		QDomNode  audioElement = root.firstChildElement(); // <audio>
		if (audioElement.nodeName() == "audio") {
			QDomNodeList nodeList;
			while (!audioElement.isNull()) {
				QDomElement element = audioElement.toElement();

				nodeList = element.elementsByTagName("aid");
				if (nodeList.count() > 0) {
					aid = nodeList.item(0).toElement().text();
				} else {
					aid.clear();
				}

				nodeList = element.elementsByTagName("owner_id");
				if (nodeList.count() > 0) {
					owner = nodeList.item(0).toElement().text();
				} else {
					owner.clear();
				}

				nodeList = element.elementsByTagName("artist");
				if (nodeList.count() > 0) {
					artist = nodeList.item(0).toElement().text();
				} else {
					artist.clear();
				}

				nodeList = element.elementsByTagName("title");
				if (nodeList.count() > 0) {
					title = nodeList.item(0).toElement().text();
				} else {
					title.clear();
				}

				nodeList = element.elementsByTagName("duration");
				if (nodeList.count() > 0) {
					duration = (unsigned int) nodeList.item(0).toElement().text().toInt();
				} else {
					duration = 0;
				}

				nodeList = element.elementsByTagName("url");
				if (nodeList.count() > 0) {
					url = nodeList.item(0).toElement().text();
				} else {
					url.clear();
				}

				item.setAid(aid);
				item.setOwner(owner);
				item.setArtist(artist);
				item.setTitle(title);
				item.setDuration(duration);
				item.setUrl(url);

				m_pItems->append(item);

				audioElement = audioElement.nextSibling();
			}
		}
	}
}

void AudioListModel::clear()
{
	m_pItems->clear();
}
