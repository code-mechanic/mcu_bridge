### Version

Format: [MM.mm.pp.bb](http://mm.mm.pp.bb/ "http://MM.mm.pp.bb")

* MM - Major version
  * Represents major release version. For initial releases this may start from “.00” numbering and may increment for a new/major product change.
* mm - Minor version
  * Represents the regular release milestones. The first release for a product may start from “.01” and this version keeps incrementing for every milestone/release.
* pp - patch version
  * Used as branching from minor release. For planned/regular milestones, patch version should be “.00”. For any patch release (branched from previous milestones), this version number increments to the next value.
* bb - build version
  * This represents the build tag within a MM.mm.pp release cycle. The first build for a release shall start with “.01”

**Note:** DO NOT USE version numbers like 1.2.1.3, instead always use two digit like 01.02.01.03

### Release Branch

Format: `<project>`_`<product>`_MM.mm<.pp><_custom qualifier>

* Note: Branch should be named all lowercase!!
* `<PROJECT>`: Refer table above for list of projects.
* `<PRODUCT>`: This represents the product that is supported for the release. Keep this same as “$PIC_SDK_HW” variable
* “.pp” is optional if branching from main branch as “.pp” of tag in main branch is always “.00”
* “_custom qualifier” is optional when we need to customer specific release branch
* Example
  * pic_sdk_pic16f877a_01.15
  * pic_sdk_pic16f877a_01.15.01
  * pic_sdk_pic16f877a_01.15_customerx
  * pic_sdk_pic16f877a_01.15.01_customerx

### Release Tag

Format: git tag -a `<PROJECT>`_`<PRODUCT>`_MM.mm.pp.bb `<COMMIT-ID>` -m “Comments”

* Note: Tag is all UPPERCASE!!
* `<PROJECT>`: Refer table above for list of projects.
* `<PRODUCT>`: This represents the product that is supported for the release. Keep this same as “$PIC_SDK_HW” variable
* `<COMMIT-ID>` : Get the commit id of your commit from “git log”
* Tagging on main branch should always have the “.pp” version number as “.00”
* While tagging in GIT, use -a option (annotated tag) and use -m to provide a meaningful message. Refer [![img](https://git-scm.com/favicon.ico)Git - Tagging](https://git-scm.com/book/en/v2/Git-Basics-Tagging)
* Example: PIC_SDK_pic194877a_00.01.00.01

```
git fetch origin

git log origin/main

# Get the <COMMIT-ID> from the previous command.

git tag -a PIC_SDK_PIC19F877A_00.01.00.01 b8c6bd770a90721ca64d034ce25b8104c5703cfc -m "PIC SDK tagging"

git push origin PIC_SDK_PIC16F877A_00.01.00.01
```
