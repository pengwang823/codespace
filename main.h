/**
 * Create a new JSGF grammar.
 *
 * @param parent optional parent grammar for this one (NULL, usually).
 * @return new JSGF grammar object, or NULL on failure.
 */
jsgf_t *jsgf_grammar_new(jsgf_t *parent);


/**
 * Parse a JSGF grammar from a file.
 *
 * @param filename the name of the file to parse.
 * @param parent optional parent grammar for this one (NULL, usually).
 * @return new JSGF grammar object, or NULL on failure.
 */
jsgf_t *jsgf_parse_file(const char *filename, jsgf_t *parent);


/**
* Parse a JSGF grammar from a string input.
*
* @param jsgf_string the jsgf string to parse 
* @return new JSGF grammar object, or NULL on failure.
*/
jsgf_t *jsgf_parse_string(const char *jsgf_string, jsgf_t *parent);


/**
* Load the vocabulary for a certain grammar.
*
* @param filename the name of the file to parse.
* @param parent optional parent grammar for this one (NULL, usually).
* @return new JSGF grammar object, or NULL on failure.
*/
jsgf_t *jsgf_load_vocab(jsgf_t *parent, const char *resource_dir, int fname);


void jsgf_update_weight(jsgf_t *gram);


/**
 * generate the semantic parsing result from a grammar file
 * @param parent optional parent grammar for this one (NULL usually)
 * @param file name th e name of the file to parse
 * @param query
 * @param tags
 * @return new grammar parsing result, or NULL on failure.
 */


jsgf_slu_t *jsgf_deduce(jsgf_t *parent, const char *rule, const char *uttr, glist_t jsgf_tag_list);


/**
 * get the next result of a certain slu parsing.
 * @param result is generated by deduce
 * @param parent optional parent grammar for this one (NULL usually)
 * @return get the next final result from the parsing result. NULL if no more result
 *  the return string will keep until the next time of calling this method.
 */


const char *jsgf_deduce_next(jsgf_slu_t *result);


void jsgf_deduce_free(jsgf_slu_t *result);


/**
 * Get the grammar name from the file.
 */
char const *jsgf_grammar_name(jsgf_t *jsgf);


/**
 * Free a JSGF grammar.
 */
void jsgf_grammar_free(jsgf_t *jsgf);


/**
 * Copy a JSGF grammar.
 */
void copy_grammar(jsgf_t *grammar);


/**
 * Iterator over rules in a grammar.
 */
typedef hash_iter_t jsgf_rule_iter_t;


/**
 * Get an iterator over all rules in a grammar.
 */
jsgf_rule_iter_t *jsgf_rule_iter(jsgf_t *grammar);


/**
 * Advance an iterator to the next rule in the grammar.
 */
#define jsgf_rule_iter_next(itor) hash_table_iter_next(itor)


/**
 * Get the current rule in a rule iterator.
 */
#define jsgf_rule_iter_rule(itor) ((jsgf_rule_t *)(itor)->ent->val)


/**
 * Free a rule iterator (if the end hasn't been reached).
 */
#define jsgf_rule_iter_free(itor) hash_table_iter_free(itor)


/**
 * Get a rule by name from a grammar.
 */
jsgf_rule_t *jsgf_get_rule(jsgf_t *grammar, char const *name);


/**
 * Attach ruleptr on atom
 */
void jsgf_atom_attach_ruleptr(jsgf_t *grammar);


/**
 * Get the rule name from a rule.
 */
char const *jsgf_rule_name(jsgf_rule_t *rule);


/**
 * Test if a rule is public or not.
 */
int jsgf_rule_public(jsgf_rule_t *rule);


/**
 * Build a Sphinx FSG object from a JSGF rule.
 */
fsg_model_t *jsgf_build_fsg(jsgf_t *grammar, jsgf_rule_t *rule,
                            logmath_t *lmath, float32 lw);


/**
 * Build a Sphinx FSG object from a JSGF rule.
 *
 * This differs from jsgf_build_fsg() in that it does not do closure
 * on epsilon transitions or any other postprocessing.  For the time
 * being this is necessary in order to write it to a file - the FSG
 * code will be fixed soon.
 */
fsg_model_t *jsgf_build_fsg_raw(jsgf_t *grammar, jsgf_rule_t *rule,
                                logmath_t *lmath, float32 lw);



/**
 * Read JSGF from file and return FSG object from it.
 *
 * This function looks for a first public rule in jsgf and constructs JSGF from it.
 */
fsg_model_t *jsgf_read_file(const char *file, logmath_t * lmath, float32 lw);


/**
 * Convert a JSGF rule to Sphinx FSG text form.
 *
 * This does a direct conversion without doing transitive closure on
 * null transitions and so forth.
 */
int jsgf_write_fsg(jsgf_t *grammar, jsgf_rule_t *rule, FILE *outfh);


/**
 * get tag from json
 */
glist_t jsgf_get_tag_list(const char *json_tag);


/**
 * free jsgf tag 
 */
void jsgf_tag_free(jsgf_tag_t *jsgf_tag);


/**
 * free jsgf tag json
 */
void jsgf_tag_list_free(glist_t jsgf_tag_list);
