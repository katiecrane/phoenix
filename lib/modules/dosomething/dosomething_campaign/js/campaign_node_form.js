(function ($) {
  $(document).ready(function(){

    // Titles of all elements that should only display when Campaign type == 'campaign'.
    var campaignTitles = ["Plan It", "Prove It"];

    // List all elements that should only display when Campaign type == 'campaign'.
    var campaignSections = [];

    $('.fieldset-title').each(function(index, value) {
      // Get the title of the fieldset and strip out unneeded text
      var title = $(value).text().replace("Show", "").trim();
      //Check if it's a campaign only title
      if (campaignTitles.indexOf(title) != -1) {
        campaignSections.push($(value).closest('.form-wrapper'));
      }
    });

    // If SMS Game, hide the campaignSections.
    if ($('#edit-field-campaign-type-und-sms-game').is(':checked')) {
      toggleSections(false);
    }

    // Listen for changes to the campaign type field.
    $('#edit-field-campaign-type-und-campaign, #edit-field-campaign-type-und-sms-game').click(function() {
      if ($('#edit-field-campaign-type-und-campaign').is(':checked')) {
        toggleSections(true);
      }
      if ($('#edit-field-campaign-type-und-sms-game').is(':checked')) {
        toggleSections(false);
      }
    });

    // Toggle the visibility of field sets in campaignSelections
    function toggleSections(show) {
      campaignSections.forEach(function($element, index, array) {
        if (show) {
          $element.show();
        }
        else {
          $element.hide();
        }
      });
    }

  });
}(jQuery));
