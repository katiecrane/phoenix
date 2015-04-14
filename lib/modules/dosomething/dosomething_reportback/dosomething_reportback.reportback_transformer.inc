<?php

abstract class ReportbackTransformer {

  public function __construct() {
    // Load Services module to use its index_query functions in subclass methods.
    module_load_include('inc', 'services', 'services.module');
  }


  /**
   * Calculate total number of Reportback items for the specified campaigns by
   * each status requested.
   *
   * @param array $parameters Query parameters.
   * @return int Total number of reportback items.
   */
  protected function countItems($parameters) {
    $total = 0;

    foreach((array) $parameters['nid'] as $id) {
      foreach((array) $parameters['status'] as $status) {
        $total += (int) dosomething_reportback_get_reportback_total_by_status($id, $status);
      }
    }

    return $total;
  }


  /**
   * @param string $data Single or multiple comma separated data items.
   * @return string or array
   */
  protected function formatData($data) {
    $array = explode(',', $data);

    if (count($array) > 1) {
      return $array;
    }

    return $data;
  }


  /**
   * @param object $object Single object of retrieved data.
   */
  abstract protected function transform($object);


  /**
   * @param array $items Collection of item objects retrieved data.
   * @return array
   */
  protected function transformCollection($items) {
    return array_map(array($this, 'transform'), $items);
  }


  /**
   * @param object $data
   * @return array
   */
  protected function transformCampaignData($data) {
    return array(
      'campaign' => array(
        'id' => $data->nid,
        'title' => $data->title,
      ),
    );
  }


  /**
   * @param object $data
   * @return array
   */
  protected function transformReportback($data) {
    $output = array(
      'id' => $data->rbid,
      'created_at' => $data->created,
      'updated_at' => $data->updated,
      'quantity' => (int) $data->quantity,
    );

    if (isset($data->why_participated)) {
      $output['why_participated'] = $data->why_participated;
    }

    if (isset($data->flagged)) {
      $output['flagged'] = (int) $data->flagged ? TRUE : FALSE;
    }

    return $output;
  }


  /**
   * @param object $data
   * @return array
   */
  protected function transformReportbackItemData($data) {
    $output = array(
      'id' => $data->fid,
      'caption' => !empty($data->caption) ? $data->caption : t('DoSomething? Just did!'),
      'uri' => $data->uri,
      'media' => array(
        'uri' => dosomething_image_get_themed_image_url_by_fid($data->fid, '480x480'),
        'type' => 'image',
      ),
      'created_at' => $data->timestamp,  // @TODO: Not sure if timestamp applies as created_at?
    );

    if (isset($data->status)) {
      $output['status'] = $data->status;
    }

    return $output;
  }


  /**
   * @param object $data
   * @return array
   */
  protected function transformUserData($data) {
    return array(
      'user' => array(
        'id' => $data->uid,
      ),
    );
  }

}