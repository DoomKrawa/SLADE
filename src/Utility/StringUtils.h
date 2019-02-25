#pragma once

#include <sstream>

class ArchiveEntry;

namespace StrUtil
{
// Static common strings
static std::string FULLSTOP              = ".";
static std::string COMMA                 = ",";
static std::string COLON                 = ":";
static std::string SEMICOLON             = ";";
static std::string SLASH_FORWARD         = "/";
static std::string SLASH_BACK            = "\\";
static std::string QUOTE_SINGLE          = "'";
static std::string QUOTE_DOUBLE          = "\"";
static std::string CARET                 = "^";
static std::string ESCAPED_QUOTE_DOUBLE  = "\\\"";
static std::string ESCAPED_SLASH_BACK    = "\\\\";
static std::string CURLYBRACE_OPEN       = "{";
static std::string CURLYBRACE_CLOSE      = "}";
static std::string DASH                  = "-";
static std::string WHITESPACE_CHARACTERS = " \t\n\r\f\v";
static std::string EMPTY                 = "";
static std::string SPACE                 = " ";
static std::string UNDERSCORE            = "_";
static std::string AMPERSAND             = "&";
static std::string EQUALS                = "=";
static std::string BOOL_TRUE             = "true";
static std::string BOOL_FALSE            = "false";

// String comparisons and checks
// CI = Case-Insensitive
bool isInteger(std::string_view str, bool allow_hex = true);
bool isHex(std::string_view str);
bool isFloat(std::string_view str);
bool equalCI(std::string_view left, std::string_view right);
// bool equalCI(string_view left, const char* right);
bool startsWith(std::string_view str, std::string_view check);
bool startsWith(std::string_view str, char check);
bool startsWithCI(std::string_view str, std::string_view check);
bool startsWithCI(std::string_view str, char check);
bool endsWith(std::string_view str, std::string_view check);
bool endsWith(std::string_view str, char check);
bool endsWithCI(std::string_view str, std::string_view check);
bool endsWithCI(std::string_view str, char check);
bool contains(std::string_view str, char check);
bool containsCI(std::string_view str, char check);
bool contains(std::string_view str, std::string_view check);
bool containsCI(std::string_view str, std::string_view check);
bool matches(std::string_view str, std::string_view match);
bool matchesCI(std::string_view str, std::string_view match);

// String transformations
// IP = In-Place
std::string  escapedString(std::string_view str, bool swap_backslash = false);
std::string& replaceIP(std::string& str, std::string_view from, std::string_view to);
std::string  replace(std::string_view str, std::string_view from, std::string_view to);
std::string& replaceFirstIP(std::string& str, std::string_view from, std::string_view to);
std::string  replaceFirst(std::string_view str, std::string_view from, std::string_view to);
std::string& lowerIP(std::string& str);
std::string& upperIP(std::string& str);
std::string  lower(std::string_view str);
std::string  upper(std::string_view str);
std::string& ltrimIP(std::string& str);
std::string& rtrimIP(std::string& str);
std::string& trimIP(std::string& str);
std::string  ltrim(std::string_view str);
std::string  rtrim(std::string_view str);
std::string  trim(std::string_view str);
std::string& capitalizeIP(std::string& str);
std::string  capitalize(std::string_view str);
std::string  wildcardToRegex(std::string_view str);
std::string  prepend(std::string_view str, std::string_view prefix);
std::string& prependIP(std::string& str, std::string_view prefix);

// Substrings
std::string              left(std::string_view str, unsigned n);
std::string_view         leftV(std::string_view str, unsigned n);
std::string              right(std::string_view str, unsigned n);
std::string_view         rightV(std::string_view str, unsigned n);
std::string              afterLast(std::string_view str, char chr);
std::string_view         afterLastV(std::string_view str, char chr);
std::string              afterFirst(std::string_view str, char chr);
std::string_view         afterFirstV(std::string_view str, char chr);
std::string              beforeLast(std::string_view str, char chr);
std::string_view         beforeLastV(std::string_view str, char chr);
std::string              beforeFirst(std::string_view str, char chr);
std::string_view         beforeFirstV(std::string_view str, char chr);
vector<std::string>      split(std::string_view str, char separator);
vector<std::string_view> splitV(std::string_view str, char separator);
std::string              truncate(std::string_view str, unsigned length);
std::string&             truncateIP(std::string& str, unsigned length);
std::string              removeLast(std::string_view str, unsigned n);
std::string&             removeLastIP(std::string& str, unsigned n);
std::string              removePrefix(std::string_view str, char prefix); // TODO: string_view prefix
std::string&             removePrefixIP(std::string& str, char prefix);
std::string              removeSuffix(std::string_view str, char suffix); // TODO: string_view suffix
std::string&             removeSuffixIP(std::string& str, char suffix);

// Misc
void processIncludes(const std::string& filename, std::string& out);
void processIncludes(ArchiveEntry* entry, std::string& out, bool use_res = true);

// Conversion
int              asInt(std::string_view str, int base = 10);
unsigned         asUInt(std::string_view str, int base = 10);
float            asFloat(std::string_view str);
double           asDouble(std::string_view str);
bool             asBoolean(std::string_view str);
bool             toInt(std::string_view str, int& target, int base = 10);
bool             toUInt(std::string_view str, unsigned& target, int base = 10);
bool             toFloat(std::string_view str, float& target);
bool             toDouble(std::string_view str, double& target);
std::string      toString(std::string_view str);
std::string_view viewFromChars(const char* chars, unsigned max_length);

// Joins all given args into a single string
template<typename... Args> std::string join(const Args&... args)
{
	std::ostringstream stream;

	int a[] = { 0, ((void)(stream << args), 0)... };

	return stream.str();
}

// Path class
class Path
{
public:
	Path(std::string_view full_path);

	const std::string& fullPath() const { return full_path_; }

	std::string_view         path(bool include_end_sep = true) const;
	std::string_view         fileName(bool include_extension = true) const;
	std::string_view         extension() const;
	vector<std::string_view> pathParts() const;
	bool                     hasExtension() const;

	void set(std::string_view full_path);
	void setPath(std::string_view path);
	void setPath(const vector<std::string_view>& parts);
	void setPath(const vector<std::string>& parts);
	void setFileName(std::string_view file_name);
	void setExtension(std::string_view extension);

	// Static functions
	static std::string_view fileNameOf(std::string_view full_path, bool include_extension = true);
	static std::string_view extensionOf(std::string_view full_path);
	static std::string_view pathOf(std::string_view full_path, bool include_end_sep = true);

private:
	std::string            full_path_;
	std::string::size_type filename_start_ = std::string::npos;
	std::string::size_type filename_end_   = std::string::npos;
};

struct Transformer
{
	std::string string;

	Transformer(std::string_view init) : string{ init } {}
	Transformer(const wxString& init) : string{ init.data(), init.size() } {}

	// Case
	Transformer& upper()
	{
		upperIP(string);
		return *this;
	}
	Transformer& lower()
	{
		lowerIP(string);
		return *this;
	}
	Transformer& capitalize()
	{
		capitalizeIP(string);
		return *this;
	}

	// Trim
	Transformer& ltrim()
	{
		ltrimIP(string);
		return *this;
	}
	Transformer& rtrim()
	{
		rtrimIP(string);
		return *this;
	}
	Transformer& trim()
	{
		trimIP(string);
		return *this;
	}
};

} // namespace StrUtil




// TODO: Remove these
namespace wxStringUtils
{
// Static common strings
static wxString FULLSTOP             = ".";
static wxString COMMA                = ",";
static wxString COLON                = ":";
static wxString SEMICOLON            = ";";
static wxString SLASH_FORWARD        = "/";
static wxString SLASH_BACK           = "\\";
static wxString QUOTE_SINGLE         = "'";
static wxString QUOTE_DOUBLE         = "\"";
static wxString CARET                = "^";
static wxString ESCAPED_QUOTE_DOUBLE = "\\\"";
static wxString ESCAPED_SLASH_BACK   = "\\\\";
static wxString CURLYBRACE_OPEN      = "{";
static wxString CURLYBRACE_CLOSE     = "}";

wxString escapedString(const wxString& str, bool swap_backslash = false);

void processIncludes(const wxString& filename, wxString& out);
void processIncludes(ArchiveEntry* entry, wxString& out, bool use_res = true);

bool isInteger(const wxString& str, bool allow_hex = true);
bool isHex(const wxString& str);
bool isFloat(const wxString& str);

int    toInt(const wxString& str);
float  toFloat(const wxString& str);
double toDouble(const wxString& str);
} // namespace wxStringUtils
