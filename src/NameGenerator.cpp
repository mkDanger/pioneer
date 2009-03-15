#include "libs.h"
#include "mtrand.h"

namespace NameGenerator {
	/* in the future the western way is the only way... :-/ */
	std::vector<std::string> forenames_male;
	std::vector<std::string> forenames_female;
	std::vector<std::string> surnames;

	void Init()
	{
		FILE *f = fopen_or_die("data/forenames_male.txt", "r");
		assert(f);
		char buf[256];
		while (fgets(buf, sizeof(buf), f)) {
			char *nl = strchr(buf, '\r');
			if (nl) *nl = 0;
			else {
				nl = strchr(buf, '\n');
				if (nl) *nl = 0;
			}
			forenames_male.push_back(std::string(buf));
		}
		fclose(f);
		f = fopen_or_die("data/forenames_female.txt", "r");
		while (fgets(buf, sizeof(buf), f)) {
			char *nl = strchr(buf, '\r');
			if (nl) *nl = 0;
			else {
				nl = strchr(buf, '\n');
				if (nl) *nl = 0;
			}
			forenames_female.push_back(std::string(buf));
		}
		fclose(f);
		f = fopen_or_die("data/surnames.txt", "r");
		while (fgets(buf, sizeof(buf), f)) {
			char *nl = strchr(buf, '\r');
			if (nl) *nl = 0;
			else {
				nl = strchr(buf, '\n');
				if (nl) *nl = 0;
			}
			surnames.push_back(std::string(buf));
		}
	}

	std::string FullName(MTRand &rng, bool genderFemale)
	{
		std::string name;
		
		if (genderFemale) {
			name = forenames_female[rng.Int32(forenames_female.size())];
		} else {
			name = forenames_male[rng.Int32(forenames_male.size())];
		}

		name += " " + surnames[rng.Int32(surnames.size())];
		return name;
	}

	std::string Surname(MTRand &rng)
	{
		return surnames[rng.Int32(surnames.size())];
	}
}
