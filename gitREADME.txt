04/21/2023
git command workflow:
https://www.google.com/url?sa=i&url=http%3A%2F%2Fkrishnaiitd.github.io%2Fgitcommands%2Fgit-workflow%2F&psig=AOvVaw3M_sZNbT8Iaol29tvJaLlN&ust=1682167993021000&source=images&cd=vfe&ved=0CBAQjRxqFwoTCND38p6Cu_4CFQAAAAAdAAAAABAE

Places code can be:
Workspace => local to you, the changes you make in a file/files
Index     => also local to you, a collection of changes you want to keep track of
Local Repository => also local to you, staging area where changes can be collected
                    to be pushed to the remote repository, where other people can
                    get them
Remote Repository => *not* local to you, this is the "centralized" place people can
                     get code from

General workflow:
1) Log in to Pi, cd to top level of the repo (~/finalProj/rit for me)

2) 'git pull' to get any changes that have been pushed to the remote repo
    since you last checked

3) Make changes/add files/etc

4) 'git status' to see what files are different/see the changes you've made

5) 'git add <path to file you changed>' to tell git that you want to include the
    change in a commit
    Example: git add gitREADME.txt 

6) Repeat 5) until all the changes you want to commit have been added

7) 'git commit -m "<commit message>"' to bundle up all of your changes into a commit
    Your commit messages don't have to be super specific, but should be more detailed
    than "fixed bug" or "added feature" =]
    Example: git commit -m "Add general git readme to top level of repo"
8) 'git push' to move your changes onto the remote server so someone else can
    check them out

Initialization:
You should be able to clone this repository with this link:
git@github.com:crl1986/IMGS362Final.git

