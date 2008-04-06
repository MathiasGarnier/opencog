/**
 * SavingLoading.h
 *
 * Copyright (c) 2001 Thiago Maia, Andre Senna
 * All rights reserved.
 */

#ifndef SAVINGLOADING_H
#define SAVINGLOADING_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>

#include "Node.h"
#include "Link.h"
#include "types.h"
#include "HandleMap.h"
#include "TruthValue.h"
#include "HandleEntry.h"
#include "SavableRepository.h"
#include "AtomSpace.h"

#ifndef WIN32
#include <ext/hash_map>
using __gnu_cxx::hash_map;
#endif

/**
 * This class provides saving and loading services based on binary images of
 * the atom table and other registered SavableRepositories
 */
class SavingLoading {
	
 private:
	
    typedef Util::hash_map<const char *, SavableRepository*, Util::hash<const char*>, Util::eqconststr> RepositoryHash;

	/**
	 * Stores the SavableRepositories actually loaded with Novamente.
	 */
	RepositoryHash repositories;

	/**
	 * This method saves ClassServer information for
	 * compatibility purposes.
	 *
	 * @param File where ClassServer info will be written.
	 */
	void saveClassServerInfo(FILE *);
	

	/**
	 * This method saves all nodes in a given file.
	 *
	 * @param File where nodes will be written.
	 * @param The table to write.
	 */
	void saveNodes(FILE *, AtomTable&, int & );
	
	/**
	 * This method saves all links in a given file.
	 *
	 * @param File where links will be written.
	 * @param The table to write.
	 */
	void saveLinks(FILE *, AtomTable&, int & );
	
	
	/**
	 * This method saves all indices in a given file.
	 *
	 * @param File where indices will be written.
	 * @param The table to write.
	 */
	void saveIndices(FILE *, AtomTable& );


	/**
	 * This method loads ClassServer information for
	 * compatibility purposes.
	 *
	 * @param File where ClassServer info will be read.
	 */
	void loadClassServerInfo(FILE *, std::vector<Type>&);
		

	/**
	 * This method loads nodes from a given file.
	 *
	 * @param File from where nodes will be read.
	 * @param Table that maps from old to new handles, necessary during
	 * loading.
	 */
	void loadNodes(FILE *, HandleMap<Atom *> *, AtomTable& );
        
	/**
	 * This method loads links from a given file.
	 *
	 * @param File from where links will be read.
	 * @param Table that maps from old to new handles, necessary during
	 * loading.
	 */
	void loadLinks(FILE *, HandleMap<Atom *> *, AtomTable& );
	
	/**
	 * This method loads indices from a given file.
	 *
	 * @param File from where indices will be read.
	 * @param Table that maps from old to new handles, necessary during
	 * loading.
	 */
	void loadIndices(FILE *, AtomTable&,  HandleMap<Atom *>*, const std::vector<Type>&);

	/**
	 * This post-loading method translates all occurrences of old handles
	 * to the new ones mapped in a hash table.
	 *
	 * @param Atom whose handles references will be translated.
	 * @param Table that maps from old to new handles.
	 */
	void updateHandles(Atom *, HandleMap<Atom *> *);
        
	/**
	 * This method writes all atom members to a given file.
	 *
	 * @param File where the atom will be written.
	 * @param Atom to be written.
	 */
	void writeAtom(FILE *, Atom *);

	/**
	 * This method writes all node members to a given file. This does not
	 * include superclass (atom) members.
	 *
	 * @param File where the node will be written.
	 * @param Node to be written.
	 */
	void writeNode(FILE *, Node *);

	/**
	 * This method writes all link members to a given file. This does not
	 * include superclass (atom) members.
	 *
	 * @param File where the link will be written.
	 * @param Link to be written.
	 */
	void writeLink(FILE *, Link *);

	/**
	 * This method writes all TruthValue members to a given file. 
	 *
	 * @param File where the TruthValue will be written.
	 * @param TruthValue to be written.
	 */
	void writeTruthValue(FILE *, const TruthValue&);

	/**
	 * This method writes all AttentionValue members to a given file. 
	 *
	 * @param File where the AttentionValue will be written.
	 * @param AttentionValue to be written.
	 * @return Number of bytes written to file.
	 */
	void writeAttentionValue(FILE *, const AttentionValue&);


	/**
	 * This method reads all atom members from a given file.
	 *
	 * @param File from where the atom will be read.
	 * @param Table to be filled with mappings from old to new handles.
	 * @param Location where the read atom will be placed.
	 */
	void readAtom(FILE *, HandleMap<Atom *> *, Atom *);

	/**
	 * This method reads all node members from a given file, and uses
	 * readAtom() to read superclass members.
	 *
	 * @param File from where the node will be read.
	 * @param Table to be filled with mappings from old to new handles.
	 * @return Newly read node.
	 */
	Node *readNode(FILE *, HandleMap<Atom *> *);

	/**
	 * This method reads all link members from a given file, and uses
	 * readAtom() to read superclass members.
	 *
	 * @param File from where the link will be read.
	 * @param Table to be filled with mappings from old to new handles.
	 * @return Newly read link.
	 */
	Link *readLink(FILE *, HandleMap<Atom *> *);

	/**
	 * This method reads all TruthValue members from a given file.
	 *
	 * @param File from where the TruthValue will be read.
	 * @return Newly read TruthValue.
	 */
	TruthValue *readTruthValue(FILE *);

	/**
	 * This method reads all AttentionValue members from a given file. 
	 *
	 * @param File from where the AttentionValue will be read.
	 * @return The newly AttentionValue read from the file.
	 */
	AttentionValue* readAttentionValue(FILE *f);


	/**
	 * This method saves the contents of all the repositories registered
	 * at the SavingLoading.
	 *
	 * @param File to where the repositories will be saved.
	 */
	void saveRepositories(FILE *);
	

	/**
	 * This method loads the contents of the repositories existent
	 * in the dump.
	 *
	 * @param File from where the repositories will be read.
	 * @param Table filled with mappings from old to new handles.
	 */
	void loadRepositories(FILE *, HandleMap<Atom *> *) throw (RuntimeException);
	

	/**
	 * This method is called to clear all the registered 
	 * repositories before a load is done,
	 */
	void clearRepositories();


	void printProgress(const char *, int);

 public:

    /**
     * Private default constructor for this class to make it abstract.
     */
    SavingLoading();
    
	/**
	 * This method saves all atoms and indices of the given AtomSpace to a
	 * file. It is a complete memory dump of the network in its current
	 * state.
	 *
	 * @param Filename where the binary image of the network will be saved.
	 */
	void save(const char *, AtomSpace&) throw (IOException);

	/**
	 * This method loads atoms and indices from a binary image in a file.
	 * Notice that there must be no atoms inserted in the table when this
	 * method is called.
	 *
	 * @param Filename from where the binary image of the network will be
	 * loaded.
	 */
	void load(const char *, AtomSpace&) throw (RuntimeException, IOException, InconsistenceException);


	/**
	 * This method includes a new SavableRepository into
	 * SavingLoading.
	 */
	void addSavableRepository(SavableRepository *) throw (RuntimeException);
};

#endif
