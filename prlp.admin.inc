<?php

/**
 * @file
 * Admin settings for PRLP.
 */

/**
 * Form builder: PRLP configuration.
 */
function prlp_admin_settings($form, &$form_state = NULL) {
  // Tell Backdrop to save values to this config object automatically.
  $form['#config'] = 'prlp.settings';

  $form['prlp'] = array(
    '#type' => 'container',
    '#tree' => FALSE,
  );

  $form['prlp']['prlp_password_required'] = array(
    '#type' => 'checkbox',
    '#title' => t('Password entry required'),
    '#description' => t('If set, users must enter a new password when they use a password reset link to log in.'),
    '#default_value' => config_get('prlp.settings', 'prlp_password_required', 1),
  );

  $form['prlp']['prlp_destination'] = array(
    '#type' => 'textfield',
    '#title' => t('Login destination'),
    '#description' => t('Path after logging in with the reset link. Use %uid to insert the user ID. Use %front for the front page.', array('%uid' => '%uid', '%front' => '<front>')),
    '#default_value' => config_get('prlp.settings', 'prlp_destination', PRLP_DESTINATION_DEFAULT),
  );

  $form['prlp']['prlp_hidden_fields'] = array(
    '#type' => 'textarea',
    '#title' => t('Fields hidden'),
    '#description' => t('Top-level form keys to hide on the reset landing page, one per line.'),
    '#default_value' => config_get('prlp.settings', 'prlp_hidden_fields', PRLP_HIDDEN_FIELDS_DEFAULT),
  );

  $form['prlp']['prlp_hidden_account_fields'] = array(
    '#type' => 'textarea',
    '#title' => t('Account fields hidden'),
    '#description' => t("Under the 'account' section (e.g., mail, name, etc.), one per line."),
    '#default_value' => config_get('prlp.settings', 'prlp_hidden_account_fields', PRLP_HIDDEN_ACCOUNT_FIELDS_DEFAULT),
  );

  $form['prlp']['prlp_confirmation_message_new_users'] = array(
    '#type' => 'textfield',
    '#title' => t('Confirmation message for new users'),
    '#description' => t('Shown to new users after they set their password.'),
    '#default_value' => config_get('prlp.settings', 'prlp_confirmation_message_new_users', 'Thank you for setting your password, the registration process has completed.'),
  );

  $form['prlp']['prlp_confirmation_message_existing_users'] = array(
    '#type' => 'textfield',
    '#title' => t('Confirmation message for existing users'),
    '#description' => t('Shown to existing users after they change their password.'),
    '#default_value' => config_get('prlp.settings', 'prlp_confirmation_message_existing_users', 'Your new password has been saved.'),
  );

  // Standard Backdrop config form wrapper (saves to #config).
  $form = system_settings_form($form);

  // Add a hard reset button that wipes config to defaults file.
  $form['actions']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset to defaults'),
    '#submit' => array('prlp_admin_settings_reset'),
    '#weight' => 50,
  );

  return $form;
}

/**
 * Submit handler for "Reset to defaults".
 */
function prlp_admin_settings_reset($form, &$form_state) {
  // Delete current settings; Backdrop will repopulate from the default JSON.
  config_delete('prlp.settings');
  backdrop_set_message(t('PRLP configuration has been reset to defaults.'));
  $form_state['rebuild'] = FALSE;
}
