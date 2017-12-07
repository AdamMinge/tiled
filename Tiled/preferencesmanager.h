/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QObject>
#include <QColor>
#include <QSize>
#include <QSettings>
/*-----------------------------------------------------------------------------------------------------------*/
class PreferencesManager final : public QObject
{
	Q_OBJECT

public:
	static PreferencesManager* instance();
	static void deleteInstance();

	PreferencesManager(PreferencesManager&&) = delete;
	PreferencesManager(const PreferencesManager&) = delete;

	PreferencesManager& operator=(PreferencesManager&&) = delete;
	PreferencesManager& operator=(const PreferencesManager&) = delete;

	const QString& style() const;
	bool showMapGrid() const;
	bool showTilesetGrid() const;
	bool showTileAnimations() const;
	bool highlightCurrentLayer() const;

	const QString& language() const;
	const QString& translationsDir() const;
	const QString& translationsPrefix() const;

	int countOfVisibleRecentDocuments() const;
	const QStringList& recentDocuments() const;
	const QString& recentDocumentDirectory() const;
	const QString& recentImageDirectory() const;

	const QByteArray& mainWindowGeometry() const;
	const QByteArray& mainWindowState() const;

	bool newTilesetUseTransparentColor() const;
	const QColor& newTilesetTransparentColor() const;
	const QSize& newTilesetTileSize() const;
	int newTilesetSpacing() const;
	int newTilesetMargin() const;

	int newMapOrientationIndex() const;
	int newMapRenderOrderIndex() const;
	const QSize& newMapSize() const;
	const QSize& newMapTileSize() const;

	const QByteArray& mapEditorState() const;
	const QSize& mapEditorSize() const;

	const QString& newPropertyType() const;

public slots:
	void setStyle(const QString& style);
	void setShowMapGrid(bool showMapGrid);
	void setShowTileAnimations(bool enabled);
	void setHighlightCurrentLayer(bool highlight);
	void setShowTilesetGrid(bool showTilesetGrid);

	void setLanguage(const QString& language);
	void setTranslationsDir(const QString& translationsDir);
	void setTranslationsPrefix(const QString& translationsPrefix);

	void setCountOfVisibleRecentDocuments(int countOfVisibleRecentDocuments);
	void setRecentDocuments(const QStringList& recentDocuments);
	void setRecentDocumentDirectory(const QString& recentDocumentDirectory);
	void setRecentImageDirectory(const QString& recentImageDirectory);

	void setMainWindowGeometry(const QByteArray& geometry);
	void setMainWindowState(const QByteArray& state);

	void setNewTilesetUseTransparentColor(bool useTransparentColor);
	void setNewTilesetTransparentColor(const QColor& transparentColor);
	void setNewTilesetTileSize(const QSize& tileSize);
	void setNewTilesetSpacing(int spacing);
	void setNewTilesetMargin(int margin);

	void setNewMapOrientationIndex(int OrientationIndex);
	void setNewMapRenderOrderIndex(int RenderOrderIndex);
	void setNewMapSize(const QSize& size);
	void setNewMapTileSize(const QSize& tileSize);

	void setMapEditorState(const QByteArray& state);
	void setMapEditorSize(const QSize& size);

	void setNewpropertyType(const QString& type);

signals:
	void styleChanged(const QString& style);
	void showMapGridChanged(bool showMapGrid);
	void showTileAnimationsChanged(bool enabled);
	void highlightCurrentLayerChanged(bool highlight);
	void showTilesetGridChanged(bool showTilesetGrid);

	void languageChanged(const QString& language);
	void translationsDirChanged(const QString& translationsDir);
	void translationsPrefixChanged(const QString& translationsPrefix);

	void countOfVisibleRecentDocumentsChanged(int countOfVisibleRecentDocuments);
	void recentDocumentsChanged(const QStringList& recentDocuments);
	void recentDocumentDirectoryChanged(const QString& recentDocumentDirectory);
	void recentImageDirectoryChanged(const QString& recentImageDirectory);

	void mainWindowGeometryChanged(const QByteArray& geometry);
	void mainWindowStateChanged(const QByteArray& state);

	void newTilesetUseTransparentColorChanged(bool useTransparentColor);
	void newTilesetTransparentColorChanged(const QColor& transparentColor);
	void newTilesetTileSizeChanged(const QSize& tileSize);
	void newTilesetSpacingChanged(int spacing);
	void newTilesetMarginChanged(int margin);

	void newMapOrientationIndexChanged(int OrientationIndex);
	void newMapRenderOrderIndexChanged(int RenderOrderIndex);
	void newMapSizeChanged(const QSize& size);
	void newMapTileSizeChanged(const QSize& tileSize);

	void mapEditorStateChanged(const QByteArray& state);
	void mapEditorSizeChanged(const QSize& size);

	void newPropertyTypeChanged(const QString& type);

private:
	explicit PreferencesManager();
	~PreferencesManager() override = default;

	int intValue(const char* key, int defaultValue = 0) const;
	bool boolValue(const char* key, bool defaultValue = false) const;
	QSize sizeValue(const char* key, const QSize& defaultValue = QSize()) const;
	QColor colorValue(const char* key, const QColor& defaultValue = QColor()) const;
	QString stringValue(const char* key, const QString& defaultValue = QString()) const;
	QStringList stringListValue(const char* key, const QStringList& defaultValue = QStringList()) const;
	QByteArray byteArrayValue(const char* key, const QByteArray& defaultValue = QByteArray()) const;

private:
	static PreferencesManager* mInstance;

	QSettings mSettings;

	QString mStyle;
	bool mHighlightCurrentLayer;
	bool mShowTileAnimations;
	bool mShowTilesetGrid;
	bool mShowMapGrid;

	QString mLanguage;
	QString mTranslationsDir;
	QString mTranslationsPrefix;

	int mCountOfVisibleRecentDocuments;
	QStringList mRecentDocuments;
	QString mRecentDocumentDirectory;
	QString mRecentImageDirectory;

	QByteArray mMainWindowGeometry;
	QByteArray mMainWindowState;

	bool mNewTilesetUseTransparentColor;
	QColor mNewTilesetTransparentColor;
	QSize mNewTilesetTileSize;
	int mNewTilesetSpacing;
	int mNewTilesetMargin;

	int mNewMapOrientationIndex;
	int mNewMapRenderOrderIndex;
	QSize mNewMapSize;
	QSize mNewMapTileSize;

	QByteArray mMapEditorState;
	QSize mMapEditorSize;

	QString mNewpropertyType;
};
/*-----------------------------------------------------------------------------------------------------------*/
