var assert = require("assert");
var greenworks = require('../greenworks');

describe('greenworks API', function() {
  if (!greenworks.initAPI()) {
    console.log('An error occured initializing Steam API.');
    process.exit(1);
  }

  describe('saveTextToFile', function() {
    it('Should save successfully.', function(done) {
      greenworks.saveTextToFile('test_file.txt', 'test_content',
          function() { done(); }, function(err) { throw err; done(); });
    });
  });

  describe('readTextFromFile', function() {
    it('Should read successfully.', function(done) {
      greenworks.readTextFromFile('test_file.txt', function(message) {
          assert(message == 'test_content'); done(); }, function(err) {
          throw err; });
    });

    it('Should read failed.', function(done) {
      greenworks.readTextFromFile('not_exist.txt', function(message) {
       throw 'Error'; }, function(err) { done(); });
    })
  });

  describe('enableCloud&isCloudEnabled', function() {
    it('', function() {
       greenworks.enableCloud(false);
       assert.equal(false, greenworks.isCloudEnabled());
       greenworks.enableCloud(true);
       assert.equal(true, greenworks.isCloudEnabled());
    });
  });

  describe('getCloudQuota', function() {
    it('Should get successfully', function(done) {
      greenworks.getCloudQuota(function(total, avail) { done(); },
                          function(err) { throw err; });
    });
  });

  describe('activateAchievement', function() {
    it('Should get successfully', function(done) {
      greenworks.activateAchievement('achievement',
                                function() { done(); },
                                function(err) { throw err; });
    });
  });

  describe('Output Steam APIs calling result', function() {
    it('Should be called successfully', function(done) {
      console.log(greenworks.getCurrentGameLanguage());
      console.log(greenworks.getCurrentUILanguage());
      console.log(greenworks.getCurrentGameInstallDir());
      console.log(greenworks.getSteamId());
      console.log(greenworks.getNumberOfPlayers(function(num) {
        console.log('Number of Players: ' + num);
        done();
      }, function(err) { throw err; }));
    });
  });

});