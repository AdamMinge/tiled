/*-----------------------------------------------------------------------------------------------------------*/
#include <QDir>
#include <QStyle>
#include <QLocale>
#include <QApplication>
#include "preferencesmanager.h"
/*-----------------------------------------------------------------------------------------------------------*/
PreferencesManager* PreferencesManager::mInstance = nullptr;
/*-----------------------------------------------------------------------------------------------------------*/
PreferencesManager* PreferencesManager::instance()
{
	if (!mInstance)
		mInstance = new PreferencesManager();

	Q_ASSERT(mInstance);
	return mInstance;
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::deleteInstance()
{
	Q_ASSERT(mInstance);
	delete mInstance;
	mInstance = nullptr;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& PreferencesManager::style() const
{
	return mStyle;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool PreferencesManager::showMapGrid() const 
{
	return mShowMapGrid;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool PreferencesManager::showTilesetGrid() const 
{
	return mShowTilesetGrid;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool PreferencesManager::showTileAnimations() const 
{
	return mShowTileAnimations;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool PreferencesManager::highlightCurrentLayer() const 
{
	return mHighlightCurrentLayer;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& PreferencesManager::language() const
{
	return mLanguage;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& PreferencesManager::translationsDir() const
{
	return mTranslationsDir;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& PreferencesManager::translationsPrefix() const
{
	return mTranslationsPrefix;
}
/*-----------------------------------------------------------------------------------------------------------*/
int PreferencesManager::countOfVisibleRecentDocuments() const 
{
	return mCountOfVisibleRecentDocuments;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QStringList& PreferencesManager::recentDocuments() const
{
	return mRecentDocuments;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& PreferencesManager::recentDocumentDirectory() const
{
	return mRecentDocumentDirectory;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QByteArray& PreferencesManager::mainWindowGeometry() const
{
	return mMainWindowGeometry;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QByteArray& PreferencesManager::mainWindowState() const
{
	return mMainWindowState;
}
/*-----------------------------------------------------------------------------------------------------------*/
bool PreferencesManager::newTilesetUseTransparentColor() const
{
	return mNewTilesetUseTransparentColor;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QColor& PreferencesManager::newTilesetTransparentColor() const
{
	return mNewTilesetTransparentColor;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QSize& PreferencesManager::newTilesetTileSize() const
{
	return mNewTilesetTileSize;
}
/*-----------------------------------------------------------------------------------------------------------*/
int PreferencesManager::newTilesetSpacing() const
{
	return mNewTilesetSpacing;
}
/*-----------------------------------------------------------------------------------------------------------*/
int PreferencesManager::newTilesetMargin() const
{
	return mNewTilesetMargin;
}
/*-----------------------------------------------------------------------------------------------------------*/
int PreferencesManager::newMapOrientationIndex() const
{
	return mNewMapOrientationIndex;
}
/*-----------------------------------------------------------------------------------------------------------*/
int PreferencesManager::newMapRenderOrderIndex() const
{
	return mNewMapRenderOrderIndex;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QSize& PreferencesManager::newMapSize() const
{
	return mNewMapSize;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QSize& PreferencesManager::newMapTileSize() const
{
	return mNewMapTileSize;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& PreferencesManager::recentImageDirectory() const
{
	return mRecentImageDirectory;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QByteArray& PreferencesManager::mapEditorState() const
{
	return mMapEditorState;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QSize& PreferencesManager::mapEditorSize() const
{
	return mMapEditorSize;
}
/*-----------------------------------------------------------------------------------------------------------*/
const QString& PreferencesManager::newPropertyType() const
{
	return mNewpropertyType;
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setStyle(const QString& style)
{
	if (mStyle == style) return;

	mStyle = style;
	mSettings.setValue(QLatin1String("Interface/Style"), mStyle);

	emit styleChanged(mStyle);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setShowMapGrid(bool showMapGrid)
{
	if (mShowMapGrid == showMapGrid) return;

	mShowMapGrid = showMapGrid;
	mSettings.setValue(QLatin1String("Interface/ShowMapGrid"), mShowMapGrid);

	emit showMapGridChanged(mShowMapGrid);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setShowTileAnimations(bool enabled)
{
	if (mShowTileAnimations == enabled) return;

	mShowTileAnimations = enabled;
	mSettings.setValue(QLatin1String("Interface/ShowTileAnimations"), mShowTileAnimations);

	emit showTileAnimationsChanged(mShowTileAnimations);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setHighlightCurrentLayer(bool highlight)
{
	if (mHighlightCurrentLayer == highlight) return;

	mHighlightCurrentLayer = highlight;
	mSettings.setValue(QLatin1String("Interface/HighlightCurrentLayer"), mHighlightCurrentLayer);

	emit highlightCurrentLayerChanged(mHighlightCurrentLayer);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setShowTilesetGrid(bool showTilesetGrid)
{
	if (mShowTilesetGrid == showTilesetGrid) return;

	mShowTilesetGrid = showTilesetGrid;
	mSettings.setValue(QLatin1String("Interface/ShowTilesetGrid"), mShowTilesetGrid);

	emit showTilesetGridChanged(mShowTilesetGrid);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setLanguage(const QString& language)
{
	if (mLanguage == language) return;

	mLanguage = language;
	mSettings.setValue(QLatin1String("Language/Language"), mLanguage);

	emit languageChanged(mLanguage);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setTranslationsDir(const QString& translationsDir)
{
	if (mTranslationsDir == translationsDir) return;

	mTranslationsDir = translationsDir;
	mSettings.setValue(QLatin1String("Language/TranslationsDir"), mTranslationsDir);

	emit translationsDirChanged(mTranslationsDir);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setTranslationsPrefix(const QString& translationsPrefix)
{
	if (mTranslationsPrefix == translationsPrefix) return;

	mTranslationsPrefix = translationsPrefix;
	mSettings.setValue(QLatin1String("Language/TranslationsPrefix"), mTranslationsPrefix);

	emit translationsPrefixChanged(mTranslationsPrefix);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setCountOfVisibleRecentDocuments(int countOfVisibleRecentDocuments)
{
	if (mCountOfVisibleRecentDocuments == countOfVisibleRecentDocuments) return;

	mCountOfVisibleRecentDocuments = countOfVisibleRecentDocuments;
	mSettings.setValue(QLatin1String("RecentFiles/CountOfVisibleRecentDocument"), mCountOfVisibleRecentDocuments);

	emit countOfVisibleRecentDocumentsChanged(mCountOfVisibleRecentDocuments);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setRecentDocuments(const QStringList& recentDocuments)
{
	if (mRecentDocuments == recentDocuments) return;

	mRecentDocuments = recentDocuments;
	mSettings.setValue(QLatin1String("RecentFiles/DocumentNames"), mRecentDocuments);

	emit recentDocumentsChanged(mRecentDocuments);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setRecentDocumentDirectory(const QString& recentDocumentDirectory)
{
	if (mRecentDocumentDirectory == recentDocumentDirectory) return;

	mRecentDocumentDirectory = recentDocumentDirectory;
	mSettings.setValue(QLatin1String("RecentFiles/DocumentDirectory"), mRecentDocumentDirectory);

	emit recentDocumentDirectoryChanged(mRecentDocumentDirectory);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setMainWindowGeometry(const QByteArray& geometry)
{
	if (mMainWindowGeometry == geometry) return;

	mMainWindowGeometry = geometry;
	mSettings.setValue(QLatin1String("MainWindow/Geometry"), mMainWindowGeometry);

	emit mainWindowGeometryChanged(mMainWindowGeometry);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setMainWindowState(const QByteArray& state)
{
	if (mMainWindowState == state) return;

	mMainWindowState = state;
	mSettings.setValue(QLatin1String("MainWindow/State"), mMainWindowState);

	emit mainWindowStateChanged(mMainWindowState);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setNewTilesetUseTransparentColor(bool useTransparentColor)
{
	if (mNewTilesetUseTransparentColor == useTransparentColor) return;

	mNewTilesetUseTransparentColor = useTransparentColor;
	mSettings.setValue(QLatin1String("NewTilesetDialog/UseTransparentColor"), mNewTilesetUseTransparentColor);

	emit newTilesetUseTransparentColorChanged(mNewTilesetUseTransparentColor);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setNewTilesetTransparentColor(const QColor& transparentColor)
{
	if (mNewTilesetTransparentColor == transparentColor) return;

	mNewTilesetTransparentColor = transparentColor;
	mSettings.setValue(QLatin1String("NewTilesetDialog/TransparentColor"), mNewTilesetTransparentColor);

	emit newTilesetTransparentColorChanged(mNewTilesetTransparentColor);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setNewTilesetTileSize(const QSize& tileSize)
{
	if (mNewTilesetTileSize == tileSize) return;

	mNewTilesetTileSize = tileSize;
	mSettings.setValue(QLatin1String("NewTilesetDialog/TileSize"), mNewTilesetTileSize);

	emit newTilesetTileSizeChanged(mNewTilesetTileSize);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setNewTilesetSpacing(int spacing)
{
	if (mNewTilesetSpacing == spacing) return;

	mNewTilesetSpacing = spacing;
	mSettings.setValue(QLatin1String("NewTilesetDialog/Spacing"), mNewTilesetSpacing);

	emit newTilesetSpacingChanged(mNewTilesetSpacing);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setNewTilesetMargin(int margin)
{
	if (mNewTilesetMargin == margin) return;

	mNewTilesetMargin = margin;
	mSettings.setValue(QLatin1String("NewTilesetDialog/Margin"), mNewTilesetMargin);

	emit newTilesetMarginChanged(mNewTilesetMargin);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setNewMapOrientationIndex(int OrientationIndex)
{
	if (mNewMapOrientationIndex == OrientationIndex) return;

	mNewMapOrientationIndex = OrientationIndex;
	mSettings.setValue(QLatin1String("NewMapDialog/OrientationIndex"), mNewMapOrientationIndex);

	emit newMapOrientationIndexChanged(mNewMapOrientationIndex);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setNewMapRenderOrderIndex(int RenderOrderIndex)
{
	if (mNewMapRenderOrderIndex == RenderOrderIndex) return;

	mNewMapRenderOrderIndex = RenderOrderIndex;
	mSettings.setValue(QLatin1String("NewMapDialog/RenderOrderIndex"), mNewMapRenderOrderIndex);

	emit newMapRenderOrderIndexChanged(mNewMapRenderOrderIndex);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setNewMapSize(const QSize& size)
{
	if (mNewMapSize == size) return;

	mNewMapSize = size;
	mSettings.setValue(QLatin1String("NewMapDialog/Size"), mNewMapSize);

	emit newMapSizeChanged(mNewMapSize);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setNewMapTileSize(const QSize& tileSize)
{
	if (mNewMapTileSize == tileSize) return;

	mNewMapTileSize = tileSize;
	mSettings.setValue(QLatin1String("NewMapDialog/TileSize"), mNewMapTileSize);

	emit newMapTileSizeChanged(mNewMapTileSize);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setRecentImageDirectory(const QString& recentImageDirectory)
{
	if (mRecentImageDirectory == recentImageDirectory) return;

	mRecentImageDirectory = recentImageDirectory;
	mSettings.setValue(QLatin1String("RecentFiles/ImageDirectory"), mRecentImageDirectory);

	emit recentImageDirectoryChanged(mRecentImageDirectory);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setMapEditorState(const QByteArray& state)
{
	if (mMapEditorState == state) return;

	mMapEditorState = state;
	mSettings.setValue(QLatin1String("MapEditor/State"), mMapEditorState);

	emit mapEditorStateChanged(mMapEditorState);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setMapEditorSize(const QSize& size)
{
	if (mMapEditorSize == size) return;

	mMapEditorSize = size;
	mSettings.setValue(QLatin1String("MapEditor/Size"), mMapEditorSize);

	emit mapEditorSizeChanged(mMapEditorSize);
}
/*-----------------------------------------------------------------------------------------------------------*/
void PreferencesManager::setNewpropertyType(const QString& type)
{
	if (mNewpropertyType == type) return;

	mNewpropertyType = type;
	mSettings.setValue(QLatin1String("AddPropertyDialog/Type"), mNewpropertyType);

	emit newPropertyTypeChanged(mNewpropertyType);
}
/*-----------------------------------------------------------------------------------------------------------*/
PreferencesManager::PreferencesManager()
{
	mSettings.beginGroup(QLatin1String("Interface"));
	mStyle = stringValue("Style", QApplication::style()->objectName());
	mHighlightCurrentLayer = boolValue("HighlightCurrentLayer", false);
	mShowTileAnimations = boolValue("ShowTileAnimations", true);
	mShowTilesetGrid = boolValue("ShowTilesetGrid", true);
	mShowMapGrid = boolValue("ShowMapGrid", true);
	mSettings.endGroup();

	mSettings.beginGroup(QLatin1String("Language"));
	mLanguage = stringValue("Language", QLocale::system().name());
	mTranslationsDir = stringValue("TranslationsDir", QLatin1String("translations"));
	mTranslationsPrefix = stringValue("TranslationsPrefix", QLatin1String("mapeditor_"));
	mSettings.endGroup();

	mSettings.beginGroup(QLatin1String("RecentFiles"));
	mCountOfVisibleRecentDocuments = intValue("CountOfVisibleRecentDocument", 10);
	mRecentDocuments = stringListValue("DocumentNames", QStringList());
	mRecentDocumentDirectory = stringValue("DocumentDirectory", QDir::homePath());
	mRecentImageDirectory = stringValue("ImageDirectory", QDir::homePath());
	mSettings.endGroup();

	mSettings.beginGroup(QLatin1String("MainWindow"));
	mMainWindowGeometry = byteArrayValue("Geometry", QByteArray());
	mMainWindowState = byteArrayValue("State", QByteArray());
	mSettings.endGroup();

	mSettings.beginGroup(QLatin1String("NewTilesetDialog"));
	mNewTilesetUseTransparentColor = boolValue("UseTransparentColor", false);
	mNewTilesetTransparentColor = colorValue("TransparentColor", QColor(255, 0, 255));
	mNewTilesetTileSize = sizeValue("TileSize", QSize(32, 32));
	mNewTilesetSpacing = intValue("Spacing", 0);
	mNewTilesetMargin = intValue("Margin", 0);
	mSettings.endGroup();

	mSettings.beginGroup(QLatin1String("NewMapDialog"));
	mNewMapOrientationIndex = intValue("OrientationIndex", 0);
	mNewMapRenderOrderIndex = intValue("RenderOrderIndex", 0);
	mNewMapSize = sizeValue("Size", QSize(100, 100));
	mNewMapTileSize = sizeValue("TileSize", QSize(32, 32));
	mSettings.endGroup();

	mSettings.beginGroup(QLatin1String("MapEditor"));
	mMapEditorState = byteArrayValue("State", QByteArray());
	mMapEditorSize = sizeValue("Size", QSize());
	mSettings.endGroup();

	mSettings.beginGroup(QLatin1String("AddPropertyDialog"));
	mNewpropertyType = stringValue("Type", QString());
	mSettings.endGroup();
}
/*-----------------------------------------------------------------------------------------------------------*/
int PreferencesManager::intValue(const char* key, int defaultValue) const
{
	return mSettings.value(QLatin1String(key), defaultValue).toInt();
}
/*-----------------------------------------------------------------------------------------------------------*/
bool PreferencesManager::boolValue(const char* key, bool defaultValue) const
{
	return mSettings.value(QLatin1String(key), defaultValue).toBool();
}
/*-----------------------------------------------------------------------------------------------------------*/
QSize PreferencesManager::sizeValue(const char* key, const QSize& defaultValue) const
{
	return mSettings.value(QLatin1String(key), defaultValue).toSize();
}
/*-----------------------------------------------------------------------------------------------------------*/
QColor PreferencesManager::colorValue(const char* key, const QColor& defaultValue) const
{
	auto name = mSettings.value(QLatin1String(key), defaultValue.name()).toString();

	if (!QColor::isValidColor(name)) return QColor();
	else return QColor(name);
}
/*-----------------------------------------------------------------------------------------------------------*/
QString PreferencesManager::stringValue(const char* key, const QString& defaultValue) const
{
	return mSettings.value(QLatin1String(key), defaultValue).toString();
}
/*-----------------------------------------------------------------------------------------------------------*/
QStringList PreferencesManager::stringListValue(const char* key, const QStringList& defaultValue) const
{
	return mSettings.value(QLatin1String(key), defaultValue).toStringList();
}
/*-----------------------------------------------------------------------------------------------------------*/
QByteArray PreferencesManager::byteArrayValue(const char* key, const QByteArray& defaultValue) const
{
	return mSettings.value(QLatin1String(key), defaultValue).toByteArray();
}
/*-----------------------------------------------------------------------------------------------------------*/
