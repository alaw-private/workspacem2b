#include <cwctype>
#include <string>
#include <vector>

#define skip_trailing_whitespace(stritr, strend) \
	while (std::iswspace(stritr)) { \
		++stritr; \
		if (stritr == strend) break; \
	}

class tag {
private:
	std::vector<tag *> nestedTags;
	std::string tagName;
	struct attrSpec {
		std::string attrName;
		std::string attrVal;
	};
	std::vector<attrSpec *> attributes;
public:
	tag(std::string name) : tagName(name) {};
	~tag()
	{
		for (attrSpec *a : attributes)
			delete a;
		for (tag *t : nestedTags)
			delete t;
	}
	void addAttr(std::string name, std::string value)
	{
		attributes.push_back(new attrSpec);
		(*attributes.end())->attrName = name;
		(*attributes.end())->attrVal = value;
	}
	tag *addTag(std::string name)
	{
		nestedTags.push_back(new tag(name));
		return *nestedTags.end();
	}
};

int main()
{
	//
}