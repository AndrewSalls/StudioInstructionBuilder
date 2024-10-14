#pragma once
#include <string>
#include <vector>
#include "geometry/mesh3d.hpp"

static class Importer {
    /**
     * Reads the geometry contained in an LDraw .ldr file, and converts it to program data.
     * 
     * @param ldrPath The file path of the LDraw file.
     * @param templateLDRFolder The file path of a collection of default LDraw parts.
     * 
     * @return An object containing all relevant geometry information, or null if failed to read file or file contained invalid formatting.
    */
    static std::vector<Mesh3D> readFile(std::string ldrPath, std::string templateLDRFolder);

    /**
     * Reads a single part from an LDraw .ldr file and converts it into a 3d mesh, potentially parsing any additional component files as well.
     * 
     * @param ldrLine The initial line being parsed.
     * @param templateLDRFolder The file path of a collection of default LDraw parts.
     * 
     * @return A Mesh3D containing all of the geometry with the initial line's part.
    */
    static Mesh3D parseLine(std::string ldrLine, std::string templateLDRFolder);
};