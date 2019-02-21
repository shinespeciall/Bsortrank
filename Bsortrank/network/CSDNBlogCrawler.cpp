#include "CSDNBlogCrawler.h"

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

networks::CSDNBlogCrawler::~CSDNBlogCrawler()
{
}

void networks::CSDNBlogCrawler::GetWebpage(QString url)
{
	QEventLoop loop;
	QNetworkAccessManager manager;
	QNetworkReply *reply = manager.get(QNetworkRequest(url));
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()), Qt::UniqueConnection);
	loop.exec();
	webpagecode = reply->readAll();
}
