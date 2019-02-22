#include "CSDNBlogCrawler.h"

/// Constructor
networks::CSDNBlogCrawler::CSDNBlogCrawler(QString _url) :
	tmp_HTML(_url)
{
	QRegExp re("^https://blog.csdn.net/[A-Za-z0-9_-]+$");
	bool match = re.exactMatch(_url);
	if(match) crawlerType = networks::PersonalBlogslist;

	QRegExp re2("^https://blog.csdn.net/[A-Za-z0-9_-]+/column/info/[0-9]+$");
	bool match2 = re2.exactMatch(_url);
	if (match2) crawlerType = networks::PersonalColumn;
}

/// Deconstructor
networks::CSDNBlogCrawler::~CSDNBlogCrawler()
{
}

/// Get Webpage and save the data inside the instance of the CSDNBlogCrawler
bool networks::CSDNBlogCrawler::GetWebpage()
{
	QEventLoop loop;
	QNetworkAccessManager manager;
	QUrl url(tmp_HTML);
	QNetworkReply *reply = manager.get(QNetworkRequest(url));
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()), Qt::UniqueConnection);
	loop.exec();
	webpagecode = reply->readAll();
	if (webpagecode.size() > 10)
		return true;
	else
		return false;
}

void networks::CSDNBlogCrawler::InitExtractionParams()
{
	QByteArray tmp = webpagecode.toUtf8();
	size_t webpagecode_size = tmp.size();
	pWebpageCode = new char[webpagecode_size];
	pWebpageCode = tmp.data();

	QString stickedTitleExtractionParam = "";
	tmp = stickedTitleExtractionParam.toUtf8();
	size_t stickedTitleExtractionParam_size = tmp.size();
	pWebpageCode = new char[stickedTitleExtractionParam_size];
	pWebpageCode = tmp.data();
}
