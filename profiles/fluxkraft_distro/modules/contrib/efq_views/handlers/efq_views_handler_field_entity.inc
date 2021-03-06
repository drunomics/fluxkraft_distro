<?php

/**
 * Field handler for entity keys.
 */
class efq_views_handler_field_entity extends views_handler_field {
  /**
   * Called to determine what to tell the clicksorter.
   */
  function click_sort($order) {
    $this->query->query->entityOrderBy($this->real_field, $order);
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['link_to_entity'] = array('default' => FALSE);
    return $options;
  }

  /**
   * Provide link to entity option
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['link_to_entity'] = array(
      '#title' => t('Link this field to its entity'),
      '#description' => t('This will override any other link you have set.'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to_entity']),
    );
  }

  /**
   * Render whatever the data is as a link to the entity.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to_entity']) && $data !== NULL && $data !== '') {
      $entity_uri = entity_uri($values->entity_type, $values);
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = $entity_uri['path'];
      $this->options['alter'] += $entity_uri['options'];
      if (isset($this->aliases['language'])) {
        $languages = language_list();
        if (isset($languages[$values->{$this->aliases['language']}])) {
          $this->options['alter']['language'] = $languages[$values->{$this->aliases['language']}];
        }
        else {
          unset($this->options['alter']['language']);
        }
      }
    }
    else {
      $this->options['alter']['make_link'] = FALSE;
    }
    return $data;
  }

  /**
   * Maps the entity keys to real returned data
   * (for example: entity_id => nid, for node).
   */
  function render($values) {
    if ($this->field == 'entity_type') {
      return $values->entity_type;
    }

    $entity_info = entity_get_info($values->entity_type);

    $id_map = array(
      'entity_id' => $entity_info['entity keys']['id'],
      'revision_id' => $entity_info['entity keys']['revision'],
      'bundle' => $entity_info['entity keys']['bundle'],
    );

    if ($this->field == 'bundle_label') {
      $value = $values->{$id_map['bundle']};
      if (isset($entity_info['bundles'][$value]['label'])) {
        $value = $entity_info['bundles'][$value]['label'];
      }
    }
    else {
      $value = $values->{$id_map[$this->field]};
    }

    return $this->render_link(check_plain($value), $values);
  }
}
