project(piProj)

include_projects_directories(LongNumber)

as_executable()

project_link_projects(LongNumber)
