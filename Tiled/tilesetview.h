/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QTableView>
/*-----------------------------------------------------------------------------------------------------------*/
class Zoomable;
class TilesetTableModel;
/*-----------------------------------------------------------------------------------------------------------*/
class TilesetView final : public QTableView
{
	Q_OBJECT

public:
	explicit TilesetView(QWidget* parent = nullptr);
	~TilesetView() override = default;

	TilesetView(TilesetView&&) = delete;
	TilesetView(const TilesetView&) = delete;

	TilesetView& operator=(TilesetView&&) = delete;
	TilesetView& operator=(const TilesetView&) = delete;

	int sizeHintForColumn(int column) const override;
	int sizeHintForRow(int row) const override;

	Zoomable* zoomable() const;
	qreal scale() const;

	bool drawGrid() const;
	void setModel(QAbstractItemModel* model) override;

	void setMarkAnimatedTiles(bool enabled);
	bool markAnimatedTiles() const;

protected:
	void wheelEvent(QWheelEvent* event) override;
	void contextMenuEvent(QContextMenuEvent* event) override;

private slots:
	void setDrawGrid(bool drawGrid);
	void adjustScale();

private:
	void resetModel(TilesetTableModel* model);
	
private:
	Zoomable* mZoomable;
	bool mDrawGrid;
	bool mMarkAnimatedTiles;
};
/*-----------------------------------------------------------------------------------------------------------*/
