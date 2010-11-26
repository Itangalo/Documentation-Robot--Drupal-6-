<?php
// $Id$

/**
 * @file
 * This file contains functions that generate documentation items for some
 * different item types.
 */

/**
 * Implementation of hook_docrobot_info().
 *
 * Documentation Robot provides this info on behalf of Drupal core.
 */
function docrobot_docrobot_info() {
  return array('module', 'role');
}

/**
 * Implementation of hook_docrobot_assemble_documentation().
 *
 * This hook is implemented on behalf of Drupal core, for several different
 * documentation item types.
 */
function docrobot_docrobot_assemble_documentation($type) {
  $items = array();

  switch ($type) {

    // Add information about enabled modules
    case 'module':
      foreach (module_rebuild_cache() as $module) {

        // Only enter enabled modules
        if ($module->status == 1) {

          // Create a fieldset for the module's project (if appropriate)
          if (!isset($items[$module->info['project']]['#name'])) {
            if (!isset($module->info['project'])) {
              $module->info['project'] = 'NO DECLARED PROJECT';
            }
            $items[$module->info['project']] = array(
              '#type' => 'fieldset',
              '#tree' => TRUE,
              '#name' => $module->info['project'],
              '#title' => $module->info['project'],
              '#collapsible' => TRUE,
            );
          }

          // Add the module itself
          $items[$module->info['project']][$module->name] = array(
            '#type' => 'markup',
            '#name' => $module->name,
            '#title' => $module->info['name'],
            '#prefix' => '<div class="docrobot-module">',
            '#value' => $module->info['name'] . ': ' . $module->info['description'],
            '#suffix' => '</div>',
          );

          // Look for any patches inside the module folder
          $patches = array();
          foreach (scandir(drupal_get_path('module', $module->name)) as $file) {
            if (preg_match('/patch/', $file)) {
              $patches[] = $file;
            }
          }
          if (count($patches)) {
            $items[$module->info['project']][$module->name]['patches'] = array(
              '#type' => 'fieldset',
              '#name' => $module->name . '-patches',
              '#title' => t('Detected patches'),
              '#description' => t('Possible patches found in the module\'s directory.'),
              '#tree' => TRUE,
              '#collapsible' => TRUE,
            );
            $i = 0;
            foreach ($patches as $patch) {
              $i++;
              $items[$module->info['project']][$module->name]['patches'][] = array(
                '#type' => 'markup',
                '#name' => $module->name . '-patch-' . $i,
                '#title' => $patch,
                '#prefix' => '<div class="docrobot-module">',
                '#value' =>
                  t('%patch: Google !search-link for this patch', array(
                  '!search-link' => l('drupal.org', 'http://www.google.com/search?q='
                  . urlencode($patch . ' link:drupal.org')),
                  '%patch' => $patch)),
                '#suffix' => '</div>',
              );
            }

          }
        }
      }

      // Return all module items for documentation
      return $items;

    // Build a list of all user roles
    case 'role' :
      foreach(user_roles() as $role) {
        $items[$role] = array(
          '#name' => $role,
          '#title' => $role,
          '#prefix' => '<div class="docrobot-role">',
          '#value' => $role,
          '#suffix' => '</div>',
        );
      }
      return $items;
    // The switch statement ends here
  }
}

/**
 * Implementation of hook_docrobot_info().
 *
 * This hook is implemented on behalf of Content.
 */
function content_docrobot_info() {
  return array('content');
}

/**
 * Implementation of hook_docrobot_assemble_documentation().
 *
 * This hook is implemented on behalf of Content.
 */
function content_docrobot_assemble_documentation($type) {
  $items = array();

  if ($type == 'content') {
    foreach (content_types() as $content_type) {
      $items[$content_type['type']] = array(
        '#type' => 'fieldset',
        '#tree' => TRUE,
        '#name' => $content_type['type'],
        '#title' => $content_type['name'],
        '#description' => $content_type['description'],
        '#collapsible' => TRUE,
      );

      if (count($content_type['fields'])) {
        $items[$content_type['type']]['fields'] = array(
          '#type' => 'fieldset',
          '#tree' => TRUE,
          '#name' => $content_type['type'] . '-fields',
          '#title' => t('CCK fields'),
          '#collapsible' => TRUE,
        );
        foreach ($content_type['fields'] as $field) {
          $items[$content_type['type']]['fields'][$field['field_name']] = array(
            '#reference' => $content_type['type'],
            '#name' => $field['widget']['type'],
            '#title' => $field['widget']['label'],
            '#prefix' => '<div class="docrobot-field">',
            '#value' => $field['widget']['label'] . ': ' . $field['widget']['description'],
            '#suffix' => '</div>',
            '#warning' => is_null($field['widget']['description']),
          );
        }
      }
    }

    // Return all the content type documentation items
    return $items;
  }

}
