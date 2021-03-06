#pragma once

#include "Archive/Archive.h"
#include "MapObjectCollection.h"
#include "MapSpecials.h"

namespace slade
{
class ParseTreeNode;
namespace Game
{
	enum class TagType;
}

class SLADEMap
{
public:
	// Map entry ordering
	enum MapEntries
	{
		THINGS = 0,
		LINEDEFS,
		SIDEDEFS,
		VERTEXES,
		SECTORS
	};

	SLADEMap();
	SLADEMap(const SLADEMap& copy) = delete;
	~SLADEMap();

	string                     mapName() const { return name_; }
	string                     udmfNamespace() const { return udmf_namespace_; }
	MapFormat                  currentFormat() const { return current_format_; }
	long                       geometryUpdated() const { return geometry_updated_; }
	long                       thingsUpdated() const { return things_updated_; }
	const MapObjectCollection& mapData() const { return data_; }

	void setGeometryUpdated();
	void setThingsUpdated();

	// MapObject access
	MapVertex*        vertex(unsigned index) const { return data_.vertices().at(index); }
	MapSide*          side(unsigned index) const { return data_.sides().at(index); }
	MapLine*          line(unsigned index) const { return data_.lines().at(index); }
	MapSector*        sector(unsigned index) const { return data_.sectors().at(index); }
	MapThing*         thing(unsigned index) const { return data_.things().at(index); }
	MapObject*        object(MapObject::Type type, unsigned index) const;
	size_t            nVertices() const { return data_.vertices().size(); }
	size_t            nLines() const { return data_.lines().size(); }
	size_t            nSides() const { return data_.sides().size(); }
	size_t            nSectors() const { return data_.sectors().size(); }
	size_t            nThings() const { return data_.things().size(); }
	const VertexList& vertices() const { return data_.vertices(); }
	const LineList&   lines() const { return data_.lines(); }
	const SideList&   sides() const { return data_.sides(); }
	const SectorList& sectors() const { return data_.sectors(); }
	const ThingList&  things() const { return data_.things(); }

	vector<ArchiveEntry*>& udmfExtraEntries() { return udmf_extra_entries_; }

	bool readMap(const Archive::MapDesc& map);
	void clearMap();

	MapSpecials* mapSpecials() { return &map_specials_; }
	void         recomputeSpecials();

	// Map saving
	bool writeMap(vector<ArchiveEntry*>& map_entries) const;

	// Creation
	MapVertex* createVertex(Vec2d pos, double split_dist = -1.);
	MapLine*   createLine(Vec2d p1, Vec2d p2, double split_dist = -1.);
	MapLine*   createLine(MapVertex* vertex1, MapVertex* vertex2, bool force = false);
	MapThing*  createThing(Vec2d pos, int type = 1);
	MapSector* createSector();
	MapSide*   createSide(MapSector* sector);

	// Removal
	bool removeVertex(MapVertex* vertex, bool merge_lines = false) { return data_.removeVertex(vertex, merge_lines); }
	bool removeVertex(unsigned index, bool merge_lines = false) { return data_.removeVertex(index, merge_lines); }
	bool removeLine(MapLine* line) { return data_.removeLine(line); }
	bool removeLine(unsigned index) { return data_.removeLine(index); }
	bool removeSide(MapSide* side, bool remove_from_line = true) { return data_.removeSide(side, remove_from_line); }
	bool removeSide(unsigned index, bool remove_from_line = true) { return data_.removeSide(index, remove_from_line); }
	bool removeSector(MapSector* sector) { return data_.removeSector(sector); }
	bool removeSector(unsigned index) { return data_.removeSector(index); }
	bool removeThing(MapThing* thing) { return data_.removeThing(thing); }
	bool removeThing(unsigned index) { return data_.removeThing(index); }
	int  removeDetachedVertices() { return data_.removeDetachedVertices(); }

	// Geometry
	BBox     bounds(bool include_things = true);
	void     updateGeometryInfo(long modified_time);
	MapLine* lineVectorIntersect(MapLine* line, bool front, double& hit_x, double& hit_y) const;

	// Tags/Ids
	void putThingsWithIdInSectorTag(int id, int tag, vector<MapThing*>& list);
	void putDragonTargets(MapThing* first, vector<MapThing*>& list);

	// Info
	string     adjacentLineTexture(MapVertex* vertex, int tex_part = 255) const;
	MapSector* lineSideSector(MapLine* line, bool front = true);
	bool       isModified() const;
	void       setOpenedTime();

	// Editing
	void       mergeVertices(unsigned vertex1, unsigned vertex2);
	MapVertex* mergeVerticesPoint(const Vec2d& pos);
	MapLine*   splitLine(MapLine* line, MapVertex* vertex);
	void       splitLinesAt(MapVertex* vertex, double split_dist = 0);
	bool       setLineSector(unsigned line_index, unsigned sector_index, bool front = true);
	int        mergeLine(unsigned index);
	bool       correctLineSectors(MapLine* line);
	void       setLineSide(MapLine* line, MapSide* side, bool front);

	// Merge
	bool     mergeArch(const vector<MapVertex*>& vertices);
	MapLine* mergeOverlappingLines(MapLine* line1, MapLine* line2);
	void     correctSectors(vector<MapLine*> lines, bool existing_only = false);

	// Checks
	void mapOpenChecks();

	// Misc. map data access
	void rebuildConnectedLines() { data_.rebuildConnectedLines(); }
	void rebuildConnectedSides() { data_.rebuildConnectedSides(); }
	void restoreObjectIdList(MapObject::Type type, vector<unsigned>& list) { data_.restoreObjectIdList(type, list); }

	// Convert
	bool convertToHexen() const;
	bool convertToUDMF();

	// Usage counts
	void clearThingTypeUsage() { usage_thing_type_.clear(); }
	void updateThingTypeUsage(int type, int adjust);
	int  thingTypeUsageCount(int type);

private:
	MapObjectCollection data_;
	string              udmf_namespace_;
	PropertyList        udmf_props_;
	string              name_;
	MapFormat           current_format_;
	long                opened_time_ = 0;
	MapSpecials         map_specials_;

	vector<ArchiveEntry*> udmf_extra_entries_; // UDMF Extras

	long geometry_updated_ = 0; // The last time the map geometry was updated
	long things_updated_   = 0; // The last time the thing list was modified

	// Usage counts
	std::map<int, int> usage_thing_type_;
};
} // namespace slade
