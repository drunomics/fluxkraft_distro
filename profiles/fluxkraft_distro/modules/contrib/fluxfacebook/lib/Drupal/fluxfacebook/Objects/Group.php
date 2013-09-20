<?php

/**
 * @file
 * Contains Group.
 */

namespace Drupal\fluxfacebook\Objects;

use Drupal\fluxfacebook\Plugin\Entity\FacebookObject;

/**
 * Entity bundle class for groups.
 */
class Group extends FacebookObject implements GroupInterface {

  /**
   * Gets the bundle property definitions.
   */
  public static function getBundlePropertyInfo($entity_type, $entity_info, $bundle) {
    // @todo Implement.
    return array();
  }

}
