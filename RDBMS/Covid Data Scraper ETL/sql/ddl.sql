use covid_data;

if object_id('dbo.continents_new') is not NULL
drop table dbo.continents_new

CREATE TABLE [dbo].[continents_new](
	[Continent] varchar(255),
	[TotalCases] varchar(255),
	[NewCases] varchar(255),
	[TotalDeaths] varchar(255),
	[NewDeaths] varchar(255),
	[TotalRecovered] varchar(255),
	[NewRecovered] varchar(255),
	[ActiveCases] varchar(255),
	[Critical] varchar(255),
);

if object_id('dbo.countries_new') is not NULL
drop table dbo.countries_new

CREATE TABLE [dbo].[countries_new](
	[Country] varchar(255),
	[TotalCases] varchar(255),
	[NewCases] varchar(255),
	[TotalDeaths] varchar(255),
	[NewDeaths] varchar(255),
	[TotalRecovered] varchar(255),
	[NewRecovered] varchar(255),
	[ActiveCases] varchar(255),
	[Critical] varchar(255),
);

if object_id('dbo.states_new') is not NULL
drop table dbo.states_new

CREATE TABLE [dbo].[states_new](
    USAState varchar(255),	
    TotalCases varchar(255),	
    NewCases varchar(255),	
    TotalDeaths varchar(255),		
    NewDeaths varchar(255),		
    TotalRecovered varchar(255),		
    ActiveCases varchar(255),		
    Total_Cases_1M_pop varchar(255),		
    Deaths_1M_pop varchar(255),		
    TotalTests varchar(255),		
    Tests varchar(255),	
	[Population] varchar(255),		
    Source varchar(255),		
    Projections varchar(255)	
);



if object_id('dbo.auxiliary_new') is not NULL
drop table dbo.auxiliary_new

CREATE TABLE [dbo].[auxiliary_new](
	[id] int,
	[iso_code] varchar(255),
	[continent] varchar(255),
	[location] varchar(255),
	[date] date,
	[population density] float,
	[median_age] float,
	aged_65_older float,
    aged_70_older float,
    gdp_per_capita float,
    extreme_poverty varchar(255),
    cardiovasc_death_rate float, 
    diabetes_prevalence	float,
    female_smokers varchar(255),
    male_smokers varchar(255),
    handwashing_facilities float,	
    hospital_beds_per_thousand	float,
    life_expectancy	float,
    human_development_index float
);

if object_id('dbo.booster_new') is not NULL
drop table dbo.booster_new

CREATE TABLE [dbo].[booster_new](
	[id] int,
	[location] varchar(255),
	[date] date,
    total_vaccinations_no_boosters float,
    total_vaccinations_no_boosters_per_hundred float,	
    total_boosters float,	
    total_boosters_per_hundred float
);

if object_id('dbo.cases_tests_new') is not NULL
drop table dbo.cases_tests_new

CREATE TABLE [dbo].[cases_tests_new](
	[id] int,
	location varchar(255),	
    [date] date,
    total_cases	float,
    new_cases float,	
    new_cases_smoothed float,	
    total_cases_per_million	float,
    new_cases_per_million float,
    new_cases_smoothed_per_million float,
    reproduction_rate float,
    new_tests float,
    total_tests	float,
	total_tests_per_thousand float,	
    new_tests_per_thousand	float,
    new_tests_smoothed	float,
    new_tests_smoothed_per_thousand float,
	positive_rate float,
    tests_per_case float,
    tests_units	varchar(255),
	share_cases_sequenced float,
    stringency_index float,
);

if object_id('dbo.deaths_new') is not NULL
drop table dbo.deaths_new

CREATE TABLE [dbo].[deaths_new](
	[id] int,
	[continent] varchar(255),
    [location] varchar(255),
	[date] date,
    total_deaths float,
    new_deaths float,	
    new_deaths_smoothed	float,
    total_deaths_per_million float,	
    new_deaths_per_million float,
    new_deaths_smoothed_per_million	float,
    cfr	float,
    cfr_short_term float
);

if object_id('dbo.hospital_new') is not NULL
drop table dbo.hospital_new

CREATE TABLE [dbo].[hospital_new](
	[id] int,
    [location] varchar(255),
	[date] date,
    icu_patients float,
    icu_patients_per_million float,
    hosp_patients varchar(255),
    hosp_patients_per_million varchar(255),
    weekly_icu_admissions varchar(255),
    weekly_icu_admissions_per_million varchar(255),
    weekly_hosp_admissions varchar(255),
    weekly_hosp_admissions_per_million varchar(255)
);

if object_id('dbo.mortality_new') is not NULL
drop table dbo.mortality_new

CREATE TABLE [dbo].[mortality_new](
	[id] int,
    [location] varchar(255),
	[date] date,
    excess_mortality float,
    excess_mortality_cumulative float,
    excess_mortality_cumulative_absolute float,	
    excess_mortality_cumulative_per_million float,	
    excess_mortality_count_week float,	
    excess_mortality_count_week_pm float,	
    cumulative_estimated_daily_excess_deaths float,	
    cumulative_estimated_daily_excess_deaths_ci_95_top float,	
    cumulative_estimated_daily_excess_deaths_ci_95_bot float,	
    cumulative_estimated_daily_excess_deaths_per_100k float,	
    cumulative_estimated_daily_excess_deaths_ci_95_top_per_100k float,	
    cumulative_estimated_daily_excess_deaths_ci_95_bot_per_100k float,
);

if object_id('dbo.vaccination_new') is not NULL
drop table dbo.vaccination_new

CREATE TABLE [dbo].[vaccination_new](
	[id] int,
    [location] varchar(255),
	[date] date,
    total_vaccination float,
    people_vaccinated float,	
    people_fully_vaccinated	float,
    total_boosters float,
    new_vaccinations float, 	
    new_vaccinations_smoothed float,	
    total_vaccinations_per_hundred float,	
    people_vaccinated_per_hundred float,	
    people_fully_vaccinated_per_hundred float,	
    total_boosters_per_hundred float,	
    new_vaccinations_smoothed_per_million float,	
    [population] float,	
    people_partly_vaccinated float,	
    people_partly_vaccinated_per_hundred float,	
    new_people_vaccinated_smoothed float,	
    new_people_vaccinated_smoothed_per_hundred float,	
    rolling_vaccinations_6m	float,
	rolling_vaccinations_6m_per_hundred	float,
    rolling_vaccinations_9m	float,
	rolling_vaccinations_9m_per_hundred float,	
    rolling_vaccinations_12m float,	
    rolling_vaccinations_12m_per_hundred float,	
    annotations varchar(255)
);

if object_id('dbo.vaccination_dose_new') is not NULL
drop table dbo.vaccination_dose_new

CREATE TABLE [dbo].[vaccination_dose_new](
	[id] int,
    [location] varchar(255),
	[date] date,
    people_fully_vaccinated	float,
    people_fully_vaccinated_per_hundred	float,
    people_partly_vaccinated float,
    people_partly_vaccinated_per_hundred float
);

if object_id('dbo.variants_new') is not NULL
drop table dbo.variants_new

CREATE TABLE [dbo].[variants_new](
	[id] int,
    [location] varchar(255),
	[date] date,
    Alpha float,
    [B.1.1.277] float,	
    [B.1.1.302] float,
    [B.1.1.519] float,
    [B.1.160] float,	
    [B.1.177] float,	
    [B.1.221] float,	
    [B.1.258] float,	
    [B.1.367] float,	
    [B.1.620] float,	
    Beta float,	
    Delta float,	
    Epsilon float,	
    Eta float,	
    Gamma float,	
    Iota float,	
    Kappa float,	
    Lambda float,	
    Mu float,	
    Omicron float,	
    [S:677H.Robin1] float,	
    [S:677P.Pelican] float,	
    non_who float,	
    others float
);