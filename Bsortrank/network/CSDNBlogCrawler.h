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
		// Constructor and Deconstructor
		CSDNBlogCrawler(QString _url);
		~CSDNBlogCrawler();

		// Functional function
		bool GetWebpage();
		void InitExtractionParams();

	private:
		// Variables
		QString tmp_HTML;
		CSDNBloglistType crawlerType = networks::PersonalBlogslist;
		QString webpagecode;
		char *pWebpageCode = nullptr;
	};
}


