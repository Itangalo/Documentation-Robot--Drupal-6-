$Id$

This module is an attempt to create basic automated technical documentation for
Drupal 6 websites. The idea is to get lists of things like node types, views,
modules/projects and user roles, and then rendering the list in various forms
(such as a single page overview, Drupal book nodes, XML data, and what not).

There is currently a hook for collecting 'documentation items', and functions
that collect and expose information about projects, modules (including patch
files), user roles and node types (including rudimentary information about CCK
fields).

The data is collected in Drupal form API format, and currently only displayed
on a single page (admin/help/docrobot).

## Future plans include
* Documentation of Views and view displays
* Extended documentation of CCK fields
* Adding of relationships between documentation items, for example relating
  node types to each other or which user roles are allowed to view Views.
* Documentation of panel pages (or Page manager pages in general), including
  variants.
* Possibility to mark certain parts of documentation items as 'desired', causing
  warning messages if they have been left empty. (For example, each CCK field
  should have a description.)

## Far-off plans include
* Automatic creation of Drupal book nodes to output documentation.
* Addition of manual notes to arbitrary documentation items (and subparts of
  them).
* Addition of completely manually entered documentation items.
* Exporting the documentation to non-Drupal formats.
