<?php

/**
 * @file
 * Provides classes for the Signup Entity.
 */

/**
 * Our Signup entity class.
 */
class SignupEntity extends Entity {

  /**
   * Override this in order to implement a custom default URI.
   */
  protected function defaultUri() {
    return array('path' => 'signup/' . $this->identifier());
  }
}

/**
 * Our custom controller for the dosomething_signup type.
 */
class SignupEntityController extends EntityAPIController {
  /**
   * Overrides buildContent() method.
   *
   * Adds Signup properties into Signup entity's render.
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    // Load user to get username.
    $account = user_load($entity->uid);
    $build = parent::buildContent($entity, $view_mode, $langcode, $content);
    $build['nid'] = array(
      '#type' => 'markup',
      '#markup' => '<p>Nid: ' . l($entity->nid, 'node/' . $entity->nid) . '</p>',
    );
    $build['username'] = array(
      '#type' => 'markup',
      '#markup' => '<p>User: ' . l($account->name, 'user/' . $account->uid) . '</p>',
    );
    $build['timestamp'] = array(
      '#type' => 'markup',
      '#markup' => '<p>Timestamp: ' . format_date($entity->timestamp, 'short') . '</p>',
    );
    if ($entity->signup_data_form_timestamp) {
      $build['signup_data_form_submitted'] = array(
        '#type' => 'markup',
        '#markup' => '<p>Signup Data Form Timestamp: ' . format_date($entity->signup_data_form_timestamp, 'short') . '</p>',
      );    
    }
    return $build;
  }
}