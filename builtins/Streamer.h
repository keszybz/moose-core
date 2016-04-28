/***
 *       Filename:  Streamer.h
 *
 *    Description:  Stream table data to a  stream.
 *
 *        Version:  0.0.1
 *        Created:  2016-04-26

 *       Revision:  none
 *
 *         Author:  Dilawar Singh <dilawars@ncbs.res.in>
 *   Organization:  NCBS Bangalore
 *
 *        License:  GNU GPL2
 */

#ifndef  Streamer_INC
#define  Streamer_INC

#define STRINGSTREAM_DOUBLE_PRECISION       10

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

#include "TableBase.h"

using namespace std;

class TableBase;

class Streamer : public TableBase
{

public:
    Streamer();
    ~Streamer();

    Streamer& operator=( const Streamer& st );

    /* Functions to set and get Streamer fields */
    void setOutFilename( string stream );
    string getOutFilename() const;

    /*  To set and get format names.  */
    void setFormat( string formatname );
    string getFormat( ) const;

    /*-----------------------------------------------------------------------------
     *  Following function adds or remove a table from vector of table tables_
     *-----------------------------------------------------------------------------*/
    void addTable( Id table );
    void addTables( vector<Id> tables);

    void removeTable( Id table );
    void removeTables( vector<Id> table );

    // Write given text to output file. Clear the text after writing it.
    void write( string& text );

    size_t getNumTables( void ) const;

    /* Dest functions.
     * The process function called by scheduler on every tick
     */
    void process(const Eref& e, ProcPtr p);

    /**
     * The reinit function called by scheduler for the reset
     */
    void reinit(const Eref& e, ProcPtr p);

    static const Cinfo * initCinfo();

private:

    // Name of the stream to which to write table data.
    string outfile_;
    string format_ = "csv";

    // delimiter in rows
    string delimiter_ = ",";

    // These Tables are handled by Streamer 
    map< Id, TableBase* > tables_;

    size_t numTables_;

    // How many lines are written to the file.
    size_t numLinesWritten_ = 0;

    // Write to file stream.
    std::ofstream of_;
    std::stringstream ss_;

    // Temporary storage to lines
    std::string text_;

    /*  Step size of this class */
    double dt_;
};

#endif   /* ----- #ifndef Streamer_INC  ----- */
