#include <algorithm>
#include <cwctype>
#include <iostream>
#include <sched.h>
#include <string>
#include <vector>

/* Helper macros */
#define ignore_trailing_whitespace(itr, end) \
	while (std::iswspace(*itr)) { ++itr; if (itr == end) break; }
#define return_to_base(tree) \
	while (tree->parent != nullptr) { tree = tree->parent; }

class tag_struct {
private:
	tag_struct *parent;
	struct _child_list {
		_child_list *prev, *next;
		tag_struct tag;
	} *child_list;
	struct _attr_list {
		_attr_list *prev, *next;
		std::string attr_name;
		std::string attr_val;
	} *attr_list;
	std::string tag_name;
public:
	tag_struct(std::string tag) : parent(nullptr), tag_name(tag),
					child_list(new _child_list),
					attr_list(new _attr_list) {};
	tag_struct(tag_struct *par, std::string tag) : parent(par), tag_name(tag) {};
	
};

struct tag_parse_node {
	tag_parse_node *prev, *next;
	std::string label;
	enum {
		TAGNAME,
		TAGATTR,
		TAGATTRVAL
	} label_type;
};

struct parsing_tree {
	parsing_tree *parent;
	std::vector<parsing_tree *> children;
	tag_parse_node *tag;
};

void construct_tag(tag_struct *ts, tag_parse_node *tn)
{
	switch (tn->label_type) {
		case tag_parse_node::TAGNAME:
			ts->tag_name = tn->label;
			break;
		case tag_parse_node::TAGATTR:
			ts->attr_list->attr_name = tn->label;
			ts->attr_list->next = new tag_struct::_attr_list(prev(ts->attr_list), .next(nullptr));
			break;
		case tag_parse_node::TAGATTRVAL:
			ts->attr_list
	}
}

void construct_tag_tree(tag_struct *ts, parsing_tree *pt)
{
	ts->
}

int main()
{
	tag_struct *tag_structure;
	unsigned lines, queries;
	std::cin >> lines;
	std::cin >> queries;
	std::cin.sync();

	tag_structure = new tag_struct;
	parsing_tree *worktree = new parsing_tree;
	worktree->parent = nullptr;
	for (int i = 0; i < lines; i++) {
		std::string workline;
		std::getline(std::cin, workline);
		int brack1 = workline.find('<');
		if (brack1 < 0)
			continue;
		int brack2 = workline.find('>');
		if (brack2 < 0 && brack1 >= 0) {
			std::cerr << "Parsing Error: could not locate closing bracket at line "
				  << i + 1 << '.';
			continue;
		}
		workline.erase(brack1);
		workline.erase(brack2);
		if (*workline.begin() == '/') {
			if (worktree->parent != nullptr
				&& worktree->parent->tag->label == workline.substr(1)) {
				worktree = worktree->parent;
				delete *worktree->children.end();
				worktree->children.pop_back();
			} else { 
				std::cerr << "Parsing Error: unexpected closing tag.";
			}
			continue;
		}
		worktree->tag = new tag_parse_node;
		tag_parse_node *working_tag = worktree->tag;
		working_tag->prev = nullptr;
		working_tag->label_type = tag_parse_node::TAGNAME;
		std::string::iterator itr = workline.begin();
		while (itr != workline.cend()) {
			if (std::iswspace(*itr)) {
				++itr;
				working_tag->next = new tag_parse_node;
				working_tag->next->prev = working_tag;
				working_tag = working_tag->next;
				working_tag->label_type = tag_parse_node::TAGATTR;
				ignore_trailing_whitespace(itr, workline.cend());
			} else if (*itr == '=') {
				++itr;
				working_tag->label_type = tag_parse_node::TAGATTRVAL;
				ignore_trailing_whitespace(itr, workline.cend());
			} else {
				working_tag->label.push_back(*itr++);
			}
		}
		working_tag->next = nullptr;
		worktree->children.push_back(new parsing_tree);
		(*worktree->children.end())->parent = worktree;
		worktree = *worktree->children.end();
	}
	return_to_base(worktree);
}