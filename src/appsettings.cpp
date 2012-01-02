#include "appsettings.h"

AppSettings::AppSettings(QObject *parent /*=0*/) : QObject(parent)
{
	m_useConfig = false;

	m_pUserDir = new QDir;
	m_pAppDir = new QDir;
	m_pSettings = new QSettings;

	m_pApp = QCoreApplication::instance();

	#ifdef Q_WS_X11
		m_pAppDir->setPath("/usr/share/vkaudiosync/");
		m_pUserDir->setPath(QDesktopServices::storageLocation(QDesktopServices::HomeLocation) + "/.VkAudioSynch/");
	#else
		m_pAppDir->setPath(m_pApp->applicationDirPath());
		m_pUserDir->setPath(m_pApp->applicationDirPath());
	#endif;
}

AppSettings::~AppSettings()
{
	delete m_pSettings;
	delete m_pAppDir;
	delete m_pUserDir;
}

void AppSettings::load()
{
	QFile file;
	QString path;

	//load settings file
	if (m_pUserDir->exists() && m_pUserDir->isReadable()) {
		path = QFile::exists(m_pUserDir->absolutePath() + QDir::separator() + "settings.ini");
		file.setFileName(path);
		if (file.exists() && file.isWritable()) {
			m_pSettings->setPath(path);
			m_useConfig = true;
		} else if (file.open(QIODevice::ReadWrite)) {
			file.close();
			m_pSettings->setPath(file.fileName());
			m_useConfig = true;
		} else {
			m_useConfig = false;
			throw QString(tr("Permision denied: Can't write ") + path);
		}
	} else {
		throw QString(tr("Permision denied: Can't read ") + m_pUserDir->path());
	}
}

