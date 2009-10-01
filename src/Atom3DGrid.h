#ifndef ATOMGRID_H
#define ATOMGRID_H

#include <vector>

#include "AtomVector.h"

using namespace std;

/*******************************************************************
   This object creates a 3D grid (based on a given size) and distributes
   atoms in the grid cells

   It can be used to ask for neighbors of an atom i (i.e. the atoms in
   the 27 cells that are neighbors of the atom's cell)

   Useful for algorithms that can use a distance based sub-list of atoms
 *******************************************************************/

class Atom3DGrid {
	public:
		Atom3DGrid();
		Atom3DGrid(AtomVector & _atoms, double _gridSize=1.0);
		~Atom3DGrid();

		unsigned int getXSize() const;
		unsigned int getYSize() const;
		unsigned int getZSize() const;

		unsigned int size() const;

		AtomVector getCell(unsigned int _i, unsigned int _j, unsigned int _k);
		AtomVector getNeighbors(unsigned int _atomIndex);
		
	private:
		void setup(AtomVector & _atoms, double _gridSize);
		void buildGrid();
		double gridSize;
		AtomVector atoms;
		vector<vector<unsigned int> > atomIndeces;
		vector<vector<vector<AtomVector> > > grid;
		double xMin;
		double xMax;
		double yMin;
		double yMax;
		double zMin;
		double zMax;
		unsigned int xSize;
		unsigned int ySize;
		unsigned int zSize;
		
};

inline AtomVector Atom3DGrid::getCell(unsigned int _i, unsigned int _j, unsigned int _k) { return grid[_i][_j][_k]; }
inline unsigned int Atom3DGrid::size() const {return atoms.size();}
inline unsigned int Atom3DGrid::getXSize() const {return xSize;}
inline unsigned int Atom3DGrid::getYSize() const {return ySize;}
inline unsigned int Atom3DGrid::getZSize() const {return zSize;}
#endif