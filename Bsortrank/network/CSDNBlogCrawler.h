#pragma once
#include <QString>
#include <QUrl>
#include <QRegExp>
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkAccessManager>

namespace networks
{
	enum CSDNBloglistType
	{
		PersonalBlogslist = 1,
		PersonalColumn    = 2
	};

	class CSDNBlogCrawler
	{
	public:
		CSDNBlogCrawler(QString _url);
		~CSDNBlogCrawler();
	private:
		QString tmp_HTML;
		CSDNBloglistType crawlerType = networks::PersonalBlogslist;
		QString webpagecode;
		void GetWebpage(QString url);
	};
}


