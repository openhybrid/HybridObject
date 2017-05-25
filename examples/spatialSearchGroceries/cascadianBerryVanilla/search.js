var obj = new HybridObject();
var positiveIcon = document.getElementById("positiveIcon");
var negativeIcon = document.getElementById("negativeIcon");

obj.addInterfaceListener(function(e, userList) {
  if (e === 'realitySearch') {
      var searchResult = obj.search(ingredients, userList);
      displaySearchResult(searchResult);
      document.getElementById("searchResultContainer").style.display = 'inline';
  } else {
      document.getElementById("searchResultContainer").style.display = 'none';
  }
});

function displaySearchResult(searchResult) {
  if (searchResult) {
      positiveIcon.className = "visibleCertification";
      negativeIcon.className = "hiddenCertification";
  } else {
      positiveIcon.className = "hiddenCertification";
      negativeIcon.className = "visibleCertification";
  }
  document.getElementById("scanner").style.display = 'none';
}