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

#include "synchservice.h"


SynchService::SynchService(QObject *parent) :
	QObject(parent)
{
	m_threadCount = 5;
/*
	connect(m_downloader, SIGNAL(modelChanged()),
			this,  SLOT(slotThreadChangeModel()));*/
}

SynchService::~SynchService()
{
//	delete[] m_downloader;
}

void SynchService::setDir(QDir *pdir)
{
	m_settings->setValue("dir",pdir->path());
	m_dir = pdir;
}

QDir* SynchService::dir() const
{
	return m_dir;
}

void SynchService::setSettings(QSettings *settings)
{
	m_settings = settings;
}

QSettings* SynchService::settings() const
{
	return m_settings;
}

void SynchService::setAudioList(QList<VK::AudioModel>* list)
{
	m_audioList = list;
}

void SynchService::synchronize()
{
	/*bool changed = false;

	if (m_dir->path().isEmpty() || !m_dir->isReadable())
		return;

	m_dir->setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot );
	QFileInfoList files = m_dir->entryInfoList();
	QList<VK::AudioModel>::iterator iterator;
	bool modelFinded ;
	for (int i = 0; i < files.size(); ++i)
	{
		modelFinded = false;
		QFileInfo fileInfo = files.at(i);
		for (iterator = m_audioList->begin(); iterator != m_audioList->end(); ++iterator)
		{
			if (VK::AudioModel::STATUS_UNDEFINED == iterator->status())
			{
				QString fullName = iterator->artist();
				fullName.append(" - ");
				fullName.append(iterator->title());
				if (fileInfo.exists() &&  fullName == fileInfo.baseName() && "mp3" == fileInfo.suffix())
				{
					modelFinded = true;
					iterator->setStatus(VK::AudioModel::STATUS_SYNCHRONIZED);
					if (!changed)
						changed = true;
				}
			}
		}
		if (modelFinded)
		{
			//TODO: upload file  to vk
		}
	}
	unsigned short threadIndex = 0, threadCounter = 0;



	for (iterator = m_audioList->begin(); iterator != m_audioList->end(); ++iterator)
	{
		if (VK::AudioModel::STATUS_UNDEFINED == iterator->status()
				|| VK::AudioModel::STATUS_NEEDDOWNLOAD == iterator->status())
		{
			iterator->setStatus(VK::AudioModel::STATUS_NEEDDOWNLOAD);

			threadIndex = threadCounter % m_threadCount;

			m_downloader[threadIndex].enqueue(&(*iterator));
			++threadCounter;

			if (!changed)
				changed = true;
		}
	}

	for (unsigned short i=0; i < m_threadCount; ++i)
	{
		m_downloader[i].setDir(m_dir);
		m_downloader[i].start();
	}

	if (changed)
		emit modelStatusesChanged();
	emit synchronizeFinished(true);*/
}

void SynchService::setThreadCount(unsigned short count)
{
	m_threadCount = count;
}

unsigned short SynchService::threadCount()
{
	return m_threadCount;
}

void SynchService::slotThreadChangeModel()
{
	emit modelStatusesChanged();
}