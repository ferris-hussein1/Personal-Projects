use covid_data;

if object_id('dbo.continents') is not NULL
drop table dbo.continents
EXEC sp_rename 'dbo.continents_new', 'continents';

if object_id('dbo.countries') is not NULL
drop table dbo.countries
EXEC sp_rename 'dbo.countries_new', 'countries';

if object_id('dbo.states') is not NULL
drop table dbo.states
EXEC sp_rename 'dbo.states_new', 'states';

if object_id('dbo.auxiliary') is not NULL
drop table dbo.auxiliary
EXEC sp_rename 'dbo.auxiliary_new', 'auxiliary';

if object_id('dbo.booster') is not NULL
drop table dbo.booster
EXEC sp_rename 'dbo.booster_new', 'booster';

if object_id('dbo.cases_tests') is not NULL
drop table dbo.cases_tests
EXEC sp_rename 'dbo.cases_tests_new', 'cases_tests';

if object_id('dbo.deaths') is not NULL
drop table dbo.deaths
EXEC sp_rename 'dbo.deaths_new', 'deaths';

if object_id('dbo.hospital') is not NULL
drop table dbo.hospital
EXEC sp_rename 'dbo.hospital_new', 'hospital';

if object_id('dbo.mortality') is not NULL
drop table dbo.mortality
EXEC sp_rename 'dbo.mortality_new', 'mortality';

if object_id('dbo.vaccination') is not NULL
drop table dbo.vaccination
EXEC sp_rename 'dbo.vaccination_new', 'vaccination';

if object_id('dbo.vaccination_dose') is not NULL
drop table dbo.vaccination_dose
EXEC sp_rename 'dbo.vaccination_dose_new', 'vaccination_dose';

if object_id('dbo.variants') is not NULL
drop table dbo.variants
EXEC sp_rename 'dbo.variants_new', 'variants';