#ifndef SJABLOON430_TOOLS_DEVICE_DATABASE_HPP
#define SJABLOON430_TOOLS_DEVICE_DATABASE_HPP

#include <string>
#include <vector>

#include "sqlite3.h"

namespace sjabloon430 { namespace tools { namespace device { namespace db {

using std::string;
using std::vector;

/* Simple data objects, no need for encapsulation in a privately used tool ... */
struct Datasheet {
	struct Date {
		// these are strings because FOR THIS PROGRAM it doesn't matter
		// the database knows the correct type and will return error(s) when incorrect!
		int month, year;
	};
	string id;
	string rev;
	Date issued;
	Date revised;
};

struct Device {
	struct Feature {
		static const int NPARAMS = 3;
		string id;
		string param[NPARAMS];
	};
	string datasheetId;
	string model;
	int maxFreq, storage, ram;
	int ngpio, nuart, nusb, ni2c, nspi, ncomp, ntimer;
	int opTempMin, opTempMax;
	vector<Device::Feature> features;
};

struct Package {
	string drawing;
	int pins;
	string type;
	bool operator==(const Package &o) const {
		return drawing == o.drawing && pins == o.pins && type == o.type;
	}
	bool operator<(const Package &o) const { // for addition to (ordered) std::set
		return drawing < o.drawing || (pins < o.pins && drawing == o.drawing);
	}
};

struct Orderable {
	string name;
	string model;
	Package pkg;
	string status;
	int msl, opTempMin, opTempMax;
};

/* SQLite 3 init */
sqlite3 *createDatabase();

/* Queries */
template<class T>
vector<T> findAll(sqlite3 *db);

template<>
vector<Datasheet> findAll<Datasheet>(sqlite3 *db);
vector<string> findDeviceFeatureIds(sqlite3 *, const string &group, const vector<string> &texts);
string findDeviceMatchFor(sqlite3 *, const string &datasheetId, const string &orderable);

/* Data modifications */
int saveOrUpdate(sqlite3 *, const Datasheet &ds);
int saveOrUpdate(sqlite3 *, const Device &dv);
int saveOrUpdate(sqlite3 *, const Orderable &);
int saveOrUpdate(sqlite3 *, const Package &);

}}}} // namespace sjabloon430::tools::device::db

template<>
struct std::hash<sjabloon430::tools::device::db::Package> {
	std::size_t operator()(const sjabloon430::tools::device::db::Package &p) const noexcept {
		std::size_t h1 = std::hash<std::string>{}(p.drawing);
		std::size_t h2 = p.pins;
		return h1 ^ (h2 << 1); // or use boost::hash_combine
	}
};
#endif // SJABLOON430_TOOLS_DEVICE_DATABASE_HPP
