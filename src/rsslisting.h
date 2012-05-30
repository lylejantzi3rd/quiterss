#ifndef RSSLISTING_H
#define RSSLISTING_H

#include <QtGui>
#include <QtSql>
#include <QtWebKit>

#include "dbmemfilethread.h"
#include "faviconloader.h"
#include "feedsmodel.h"
#include "feedsview.h"
#include "newsheader.h"
#include "newsmodel.h"
#include "newstabwidget.h"
#include "newsview.h"
#include "parsethread.h"
#include "updateappdialog.h"
#include "updatethread.h"
#include "webview.h"

class RSSListing : public QMainWindow
{
  Q_OBJECT
public:
  RSSListing(QSettings *settings, QString dataDirPath, QWidget *parent = 0);
  ~RSSListing();
  bool showSplashScreen_;
  bool showTrayIcon_;
  bool startingTray_;
  QSystemTrayIcon *traySystem;
  void setCurrentFeed();

  QSettings *settings_;
  QSqlDatabase db_;
  FeedsModel *feedsModel_;
  FeedsView *feedsView_;

  QAction *newsFilter_;
  QAction *openInBrowserAct_;
  QAction *openInExternalBrowserAct_;
  QAction *markNewsRead_;
  QAction *markAllNewsRead_;
  QAction *markStarAct_;
  QAction *updateFeedAct_;
  QAction *deleteNewsAct_;
  QAction *newsKeyUpAct_;
  QAction *newsKeyDownAct_;
  QActionGroup *newsFilterGroup_;

  QString newsFontFamily_;
  int newsFontSize_;
  QString webFontFamily_;
  int webFontSize_;

  bool markNewsReadOn_;
  int  markNewsReadTime_;

  bool autoLoadImages_;

  bool embeddedBrowserOn_;
  bool javaScriptEnable_;
  bool pluginsEnable_;

  bool showDescriptionNews_;

public slots:
  void addFeed();
  void deleteFeed();
  void slotImportFeeds();
  void slotExportFeeds();
  void slotFeedsTreeClicked(QModelIndex index);
  void slotFeedsTreeSelected(QModelIndex index, bool clicked = false,
                             bool createTab = false);
  void slotGetFeed();
  void slotGetAllFeeds();
  void showOptionDlg();
  void receiveMessage(const QString&);
  void slotPlaceToTray();
  void slotActivationTray(QSystemTrayIcon::ActivationReason reason);
  void slotShowWindows(bool trayClick = false);
  void slotClose();
  void slotCloseApp();
  void myEmptyWorkingSet();
  void receiveXml(const QByteArray &data, const QUrl &url);
  void getUrlDone(const int &result, const QDateTime &dtReply);
  void slotUpdateFeed(const QUrl &url, const bool &changed);
  void slotUpdateStatus(bool openFeed = true);
  void setNewsFilter(QAction*, bool clicked = true);

protected:
  bool eventFilter(QObject *obj, QEvent *ev);
  virtual void closeEvent(QCloseEvent*);
  virtual void changeEvent(QEvent*);
  virtual void showEvent(QShowEvent*);
  void timerEvent(QTimerEvent* event);

private:
  UpdateThread *persistentUpdateThread_;
  ParseThread *persistentParseThread_;
  QNetworkProxy networkProxy_;

  void showProgressBar(int addToMaximum);
  void createFeedsDock();
  void createNewsTab();
  void createToolBarNull();
  void createActions();
  void createShortcut();
  void loadActionShortcuts();
  void saveActionShortcuts();
  void createMenu();
  void createToolBar();
  void readSettings ();
  void writeSettings();
  void createTrayMenu();
  void createMenuFeed();
  void createStatusBar();
  void createTray();
  void loadSettingsFeeds();
  bool sqliteDBMemFile(QSqlDatabase memdb, QString filename, bool save);
  void appInstallTranslator();
  void retranslateStrings();
  void refreshInfoTray();
  void playSoundNewNews();
  void feedsCleanUp(QString feedId);
  void recountFeedCounts(int feedId, QModelIndex index = QModelIndex());

  QString dataDirPath_;

  QString dbFileName_;
  NewsModel *newsModel_;
  QTabWidget *tabWidget_;
  QTabBar* tabBar_;

  QList<QAction *> listActions_;
  QStringList listDefaultShortcut_;

  QAction *addFeedAct_;
  QAction *deleteFeedAct_;
  QAction *importFeedsAct_;
  QAction *exportFeedsAct_;
  QAction *toolBarToggle_;
  QAction *toolBarStyleI_;
  QAction *toolBarStyleT_;
  QAction *toolBarStyleTbI_;
  QAction *toolBarStyleTuI_;
  QAction *toolBarIconSmall_;
  QAction *toolBarIconNormal_;
  QAction *toolBarIconBig_;
  QAction *systemStyle_;
  QAction *system2Style_;
  QAction *greenStyle_;
  QAction *orangeStyle_;
  QAction *purpleStyle_;
  QAction *pinkStyle_;
  QAction *grayStyle_;
  QAction *autoLoadImagesToggle_;
  QAction *setNewsFiltersAct_;
  QAction *setFilterNewsAct_;
  QAction *optionsAct_;
  QAction *updateAllFeedsAct_;
  QAction *markAllFeedRead_;
  QAction *exitAct_;
  QAction *feedsFilter_;
  QAction *filterFeedsAll_;
  QAction *filterFeedsNew_;
  QAction *filterFeedsUnread_;

  QAction *filterNewsAll_;
  QAction *filterNewsNew_;
  QAction *filterNewsUnread_;
  QAction *filterNewsStar_;
  QAction *aboutAct_;
  QAction *updateAppAct_;

  QAction *markFeedRead_;
  QAction *feedProperties_;
  QAction *showWindowAct_;
  QAction *feedKeyUpAct_;
  QAction *feedKeyDownAct_;
  QAction *switchFocusAct_;
  QAction *visibleFeedsDockAct_;
  QAction *openNewTabAct_;

  QActionGroup *toolBarStyleGroup_;
  QActionGroup *toolBarIconSizeGroup_;
  QActionGroup *styleGroup_;
  QActionGroup *feedsFilterGroup_;

  QAction *feedsFilterAction;
  QAction *newsFilterAction;

  QAction *showUnreadCount_;
  QAction *showUndeleteCount_;
  QAction *showLastUpdated_;
  QActionGroup *feedsColumnsGroup_;

  QMenu *fileMenu_;
  QMenu *editMenu_;
  QMenu *viewMenu_;
  QMenu *toolBarMenu_;
  QMenu *toolBarStyleMenu_;
  QMenu *toolBarIconSizeMenu_;
  QMenu *styleMenu_;
  QMenu *feedMenu_;
  QMenu *newsMenu_;
  QMenu *toolsMenu_;
  QMenu *helpMenu_;
  QMenu *trayMenu_;
  QMenu *newsContextMenu_;
  QMenu *feedContextMenu_;
  QMenu *feedsFilterMenu_;
  QMenu *newsFilterMenu_;
  QMenu *feedsColumnsMenu_;

  QToolBar *toolBar_;

  QLabel *feedsTitleLabel_;
  QToolBar *feedsToolBar_;
  QDockWidget *feedsDock_;
  Qt::DockWidgetArea feedsDockArea_;

  NewsView *newsView_;
  WebView *webView_;

  NewsTabWidget *currentNewsTab;

  int oldState;

  QProgressBar *progressBar_;
  QLabel *statusUnread_;
  QLabel *statusAll_;

  QToolBar *toolBarNull_;
  QPushButton *pushButtonNull_;

  QByteArray data_;
  QUrl url_;

  QBasicTimer updateFeedsTimer_;
  bool autoUpdatefeedsStartUp_;
  bool autoUpdatefeeds_;
  int  autoUpdatefeedsTime_;
  int  autoUpdatefeedsInterval_;

  QTranslator *translator_;
  QString langFileName_;

  bool minimizingTray_;
  bool closingTray_;
  bool singleClickTray_;
  bool clearStatusNew_;
  bool emptyWorking_;
  int behaviorIconTray_;

  int openingFeedAction_;
  bool openNewsWebViewOn_;

  FaviconLoader *faviconLoader;

  DBMemFileThread *dbMemFileThread_;
  bool commitDataRequest_;

  bool soundNewNews_;
  bool playSoundNewNews_;

  UpdateAppDialog *updateAppDialog_;

  int maxDayCleanUp_;
  int maxNewsCleanUp_;
  bool dayCleanUpOn_;
  bool newsCleanUpOn_;
  bool readCleanUp_;
  bool neverUnreadCleanUp_;
  bool neverStarCleanUp_;

  bool showMessageOn_;

  bool reopenFeedStartup_;

private slots:
  void slotProgressBarUpdate();
  void slotVisibledFeedsDock();
  void updateIconToolBarNull(bool feedsDockVisible);
  void slotDockLocationChanged(Qt::DockWidgetArea area);
  void slotFeedsDockLocationChanged(Qt::DockWidgetArea area);

  void setFeedRead(int feedId);
  void markFeedRead();
  void setFeedsFilter(QAction*, bool clicked = true);

  void slotShowAboutDlg();

  void showContextMenuFeed(const QPoint &);
  void setAutoLoadImages();
  void slotFeedsFilter();
  void slotNewsFilter();
  void slotTimerUpdateFeeds();
  void slotShowUpdateAppDlg();
  void setToolBarStyle(QAction*);
  void setToolBarIconSize(QAction*);
  void showContextMenuToolBar(const QPoint &);
  void slotShowFeedPropertiesDlg();
  void slotFeedMenuShow();
  void slotNewsMenuShow();
  void slotNewsActionEnabled(bool enable);
  void markAllFeedsRead(bool readOn = true);
  void slotIconFeedLoad(const QString& strUrl, const QByteArray &byteArray);
  void slotCommitDataRequest(QSessionManager&);
  void showNewsFiltersDlg();
  void showFilterNewsDlg();
  void slotUpdateAppChacking();
  void slotNewVersion(bool newVersion);
  void slotFeedUpPressed();
  void slotFeedDownPressed();
  void slotFeedHomePressed();
  void slotFeedEndPressed();
  void setStyleApp(QAction*);
  void slotSwitchFocus();
  void slotOpenNewTab();
  void slotTabCloseRequested(int index);
  void slotTabCurrentChanged(int index);
  void feedsColumnVisible(QAction* action);

signals:
  void signalPlaceToTray();
  void signalCloseApp();
  void startGetUrlTimer();
  void xmlReadyParse(const QByteArray &data, const QUrl &url);
};

#endif

