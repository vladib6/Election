#include "Save.h"

void Save::runSave() const 
{
	std::ofstream outfile(FileName.getString(), std::ios::binary);
	outfile.write(rcastcc(&elecType), sizeof(elecType));
	if (!outfile) {
		throw std::ios_base::failure("Error with file");
	}
	E->save(outfile);
	outfile.close();
}
