"use strict";

// Variables
let curWebPage;
let curPage = 1;
let globalArticles;
let activeCategoryID;

const mdMediaQuery = "(max-width:768px)";
const smMediaQuery = "(max-width:576px)";

const navbars = document.querySelectorAll(".navigation");
const homeNav = document.querySelector(".home-navbar");
const layoutNav = document.querySelector(".layout-nav");
const homeNavLinks = document.querySelectorAll(".homenav-link");
const navLinks = document.querySelectorAll(".nav-link");
const navHeight = layoutNav.getBoundingClientRect().height;

const allSections = document.querySelectorAll(".section");

const header = document.querySelector(".home-header");
const homePage = document.querySelector("#homepage");

const blogPage = document.querySelector("#blogPage");
const linksContainer = document.querySelector(".category__link--container");
const dropdownMenu = document.querySelector(".dropdown-menu");
const articleContainer = document.querySelector(".articles-container");

const galleryPage = document.querySelector("#galleryPage");

////////////////////////////////////////////////Home///////////////////////////////////////////////////////////
// Chnage according to intersection
const stickyNav = function (entries) {
  // selecting the first element
  const [entry] = entries;
  if (!entry.isIntersecting) {
    homeNav.style.display = "none";
    layoutNav.style.display = "block";
    layoutNav.classList.add("sticky");
  } else {
    if (layoutNav.classList.contains("sticky")) layoutNav.style.transform = "translateY(-100%)";
    setTimeout(() => {
      homeNav.style.display = "block";
      layoutNav.style.display = "none";
      layoutNav.classList.remove("sticky");

      layoutNav.style.transform = "translateY(0%)";
    }, 700);
  }
};
const headerObserver = new IntersectionObserver(stickyNav, {
  root: null,
  threshold: 0,
  rootMargin: `-${navHeight + 80}px`,
});

// Change according to the page
const navbarManipulation = function (page) {
  curWebPage = page;

  homeNavLinks.forEach((navlink) => navlink.classList.remove("homeNav-active"));
  navLinks.forEach((navlink) => navlink.classList.remove("layoutNav-active"));

  homeNav.querySelector(`[data-page=${page}]`).classList.add("homeNav-active");
  layoutNav.querySelector(`[data-page=${page}]`).classList.add("layoutNav-active");

  if (curWebPage === "home") {
    headerObserver.observe(header);
  } else {
    homeNav.style.display = "none";
    layoutNav.style.display = "block";
  }
};

// Navbar Fade Animation
const handleHover = function (e) {
  if (e.target.classList.contains("nav-link")) {
    const link = e.target;
    const siblings = link.closest("nav").querySelectorAll(".nav-link");
    const title = link.closest("nav").querySelector(".navbar-brand");

    siblings.forEach((el) => {
      if (el != link) el.style.opacity = this;
    });
    title.style.opacity = this;
  }
};

// Swapping Text & Image Columns
const swap = function () {
  // matched or not
  const matched = this.matches;
  const imageColumn = document.querySelector("#row--2 .section__one-image");
  imageColumn.style.display = "none";

  // if screen is below 768 px
  if (matched) {
    imageColumn.style.display = "block";
    document.querySelector("#row--2").insertAdjacentElement("beforeend", imageColumn);
  } else {
    imageColumn.style.display = "block";
    document.querySelector("#row--2").insertAdjacentElement("afterbegin", imageColumn);
  }
};

// Reveal Section
const revealSection = function (entries, observer) {
  const [entry] = entries;
  if (!entry.isIntersecting) return;
  entry.target.classList.remove("section--hidden");
  observer.unobserve(entry.target);
};
const sectionObserver = new IntersectionObserver(revealSection, {
  root: null,
  threshold: 0.15,
});

// Home Slider
const slider = function () {
  // variables
  const slides = document.querySelectorAll(".home-slide");
  const btnLeft = document.querySelector(".slider__btn--left");
  const btnRight = document.querySelector(".slider__btn--right");
  const dotContainer = document.querySelector(".dots");

  let curSlide = 0;
  const maxSlide = slides.length;

  // functions
  const createDots = function () {
    slides.forEach((_, i) => {
      dotContainer.insertAdjacentHTML("beforeend", `<button class="dots__dot" data-slide="${i}"></button>`);
    });
  };

  const activateDot = function (slide) {
    document.querySelectorAll(".dots__dot").forEach((dot) => {
      dot.classList.remove("dots__dot--active");
      if (Number(dot.dataset.slide) === Number(slide)) {
        dot.classList.add("dots__dot--active");
      }
    });
  };

  const goToSlide = function (slide) {
    slides.forEach((s, i) => (s.style.transform = `translateX(${(i - slide) * 100}%)`));
    activateDot(slide);
  };
  // 0%, 100%, 200%, 300%

  const nextSlide = function () {
    if (curSlide === maxSlide - 1) {
      curSlide = 0;
    } else {
      curSlide++;
    }
    goToSlide(curSlide);
  };

  const prevSlide = function () {
    if (curSlide === 0) {
      curSlide = maxSlide - 1;
    } else {
      curSlide--;
    }
    goToSlide(curSlide);
  };

  // initialization
  const init = function () {
    createDots();
    goToSlide(0);
  };
  init();

  // event handlers
  btnRight.addEventListener("click", nextSlide);
  btnLeft.addEventListener("click", prevSlide);

  document.addEventListener("keydown", function (e) {
    if (e.key === "ArrowLeft") prevSlide();
    else if (e.key === "ArrowRight") nextSlide();
  });

  dotContainer.addEventListener("click", function (e) {
    if (e.target.classList.contains("dots__dot")) {
      // fancy destructuring object
      const { slide } = e.target.dataset;
      goToSlide(slide);
    }
  });
};

////////////////////////////////////////Blog///////////////////////////////////////////
// Read a Particular Article
const readArticle = function (e) {
  const articlePage = document.querySelector("#articlePage");
  const article_id = e.target.closest(".article-card")?.id;

  window.scrollTo(0, 0);
  if (article_id) {
    fetch(`/read_article/${article_id}`)
      .then((response) => response.json())
      .then((article) => {
        const html = `
          <div class="article-container">
          <img
            src="${article.image}"
            class="card-img-top"
            alt="${article.title}"
          />
          <div class="article card">
            <div class="card-body">
              <h1 class="text-center">${article.title}</h1>
              <span class="badge bg-${article.color}">${article.category}</span>
              <br />
              <i class="text-muted">${article.timestamp}</i>
              <p class="card-text">
                ${article.content}
              </p>
            </div>
          </div>
        </div>
          `;
        document.querySelectorAll(".webpage").forEach((page) => (page.style.display = "none"));

        articlePage.style.display = "block";
        articlePage.innerHTML = html;
      });
  }
};

// Insert Article Cards into Page
const insertArticles = function (articles, pageNum) {
  const articlesPerPage = 2;
  const pagesCount = Math.ceil(articles.length / articlesPerPage);
  const slicedArticles = articles.slice((pageNum - 1) * articlesPerPage, pageNum * articlesPerPage);
  const pagination = document.querySelector(".pagination");
  const articlesContainer = document.querySelector(".articles-container");

  curPage = Number(pageNum);
  globalArticles = articles;

  // Create Articles
  articlesContainer.innerHTML = "";
  slicedArticles.forEach((article) => {
    const html = `
        <div class="col-md-4 col-sm-6 col-12">
          <div class="article-card card" id="${article.id}">
              <img src="${article.image}" class="card-img-top" alt="..." />
            <div class="card-body">
              <h5 class="card-title">${article.title}</h5>
              <span class="badge bg-${article.category_color[0]}">${article.category}</span>
            </div>
          </div>
        </div>
        `;
    articlesContainer.insertAdjacentHTML("beforeend", html);
  });

  // Create Pagination links
  const first = `
    <li class="page-item"><a class="page-link working-page-link" data-pg=1>first</a></li>
    `;
  const previous = `
    <li class="page-item">
      <a class="page-link working-page-link" data-pg=${curPage - 1}
        ><span aria-hidden="true">&laquo;</span></a
      >
    </li>
    `;
  const now = `
    <li class="page-item">
      <a class="page-link"
        >Page ${curPage} of ${pagesCount}</a
      >
    </li>
    `;
  const next = `
    <li class="page-item">
      <a class="page-link working-page-link" data-pg=${curPage + 1}
        ><span aria-hidden="true">&raquo;</span></a
      >
    </li>
    `;
  const last = `
    <li class="page-item">
      <a class="page-link working-page-link" data-pg=${pagesCount}
        >last</a
      >
    </li>
    `;

  // Insert links
  let html;
  if (pagesCount === 1) html = "";
  else if (curPage === 1) html = now.concat(next).concat(last);
  else if (curPage === pagesCount) html = first.concat(previous).concat(now);
  else html = first.concat(previous).concat(now).concat(next).concat(last);

  pagination.innerHTML = "";
  pagination.insertAdjacentHTML("afterbegin", html);
};

// Create Category Links
const createCategoryLinks = function (categoryArray) {
  const linksContainer = document.querySelector(".category__link--container");
  const dropdown = document.querySelector(".dropdown");
  const dropdownMenu = document.querySelector(".dropdown-menu");

  const matched = window.matchMedia(smMediaQuery).matches;
  // if screen is below 576 px
  if (matched) {
    linksContainer.style.display = "none";
    dropdown.style.display = "block";
    dropdownMenu.innerHTML = "";

    let html;
    categoryArray.forEach((category) => {
      if (category.id === activeCategoryID)
        html = `
      <li><button class="category__link dropdown-item link-active" data-category="${category.id}">${category.title}</button></li>
    `;
      else
        html = `
              <li><button class="category__link dropdown-item" data-category="${category.id}">${category.title}</button></li>
          `;

      dropdownMenu.insertAdjacentHTML("beforeend", html);
    });
  } else {
    dropdown.style.display = "none";
    linksContainer.style.display = "block";
    linksContainer.innerHTML = "";

    categoryArray.forEach((category) => {
      let html;
      if (category.id === activeCategoryID)
        html = `
                <a class="category__link link-item link-active" data-category="${category.id}">${category.title}</a>
                `;
      else
        html = `
              <a class="category__link link-item" data-category="${category.id}">${category.title}</a>
              `;

      linksContainer.insertAdjacentHTML("beforeend", html);
    });
  }
};

// Create Category Intro Card
const createCategoryIntro = function (categoryID) {
  const categoryIntro = document.querySelector(".category-intro");
  const categoryTabsContainer = document.querySelector(".category-tabs-container");
  const activeCategoryLinks = categoryTabsContainer.querySelectorAll(`[data-category='${categoryID}']`);
  const categoryLinks = document.querySelectorAll(".category__link");

  fetch(`/request_category/${categoryID}`)
    .then((response) => response.json())
    .then((category) => {
      const html = `
        <h1>${category.title}</h1>
        <img
          width="160"
          class="img-fluid"
          src="${category.image}"
          alt="${category.title}"
        /><br /><br />
        <p>${category.text}</p>
        `;
      categoryIntro.innerHTML = "";
      categoryIntro.insertAdjacentHTML("afterbegin", html);
    });

  categoryLinks.forEach((link) => link.classList.remove("link-active"));
  activeCategoryLinks.forEach((link) => link.classList.add("link-active"));
  activeCategoryID = Number(categoryID);
};

// Request Article Cards
const requestArticles = function (categoryID) {
  createCategoryIntro(categoryID);

  fetch(`/request_articles/${categoryID}`)
    .then((response) => response.json())
    .then((articles) => {
      // always show the first page of the requested category
      insertArticles(articles, 1);
    });
};

////////////////////////////////Gallery///////////////////////////////////
// Render Images in the Gallery
const renderImages = function (images) {
  const section = document.querySelector(".gallery-section");
  const imagesObject = {};

  // Create a list for each category
  images.forEach((image) => {
    imagesObject[image.category.toUpperCase()] = [];
  });

  // Push images into the list of their respective category
  images.forEach((image) => {
    imagesObject[image.category.toUpperCase()].push(image);
  });

  let sliderNum = 0;
  for (const [category, list] of Object.entries(imagesObject)) {
    const html = `
    <div class="category-container">
      <h1>${category}</h1>
      <div class="slider" id="slider-${sliderNum}"></div>
      <br>
      <div class="show_image"></div>
    </div>
    <hr>
    `;

    section.insertAdjacentHTML("beforeend", html);

    list.forEach((image, i) => {
      const img = `
      <div class="slide" data-slide="${i}">
        <img src="${image.image}" alt="${image.name}" />
        <div class="overlay" style="display:none"></div>
      </div>
      `;

      document.querySelector(`#slider-${sliderNum}`).insertAdjacentHTML("beforeend", img);
    });

    sliderNum++;
  }
};

// Implement Slider
const gallerySlider = function () {
  // variables
  const section = document.querySelector(".gallery-section");
  const sliders = document.querySelectorAll(".slider");

  const curSlide = {};
  const maxSlide = {};
  sliders.forEach((slider) => {
    curSlide[slider.id] = 0;
    maxSlide[slider.id] = slider.querySelectorAll(".slide").length;
  });

  // functions
  const goToSlide = function (slideNum, slider) {
    slider.querySelectorAll(".slide").forEach((s, i) => {
      s.querySelector(".overlay").style.display = "block";
      s.style.transform = `translateX(${(i - slideNum) * 100}%)`;
    });

    const slide = slider.querySelector(`[data-slide='${slideNum}']`);
    slide.querySelector(".overlay").style.display = "none";

    // curSlide should be updated by clicking as well
    curSlide[slider.id] = slideNum;
  };

  const nextSlide = function (slider) {
    if (curSlide[slider.id] === maxSlide[slider.id] - 1) {
      curSlide[slider.id] = 0;
    } else {
      curSlide[slider.id]++;
    }
    goToSlide(curSlide[slider.id], slider);
  };

  // Show a particular Image
  const showImage = function (slideNum, slider) {
    const image = slider.querySelector(`[data-slide='${slideNum}']`).firstElementChild;

    const html = `
    <img src="${image.src}" alt="${image.alt}" />
    <h3>${image.alt}</h3>
    `;

    const imageContainer = slider.parentElement.querySelector(".show_image");
    imageContainer.innerHTML = "";
    imageContainer.insertAdjacentHTML("beforeend", html);
  };
  // Initialising
  sliders.forEach((slider) => {
    goToSlide(0, slider);
    showImage(0, slider);

    // event handlers
    setInterval(() => {
      nextSlide(slider);
    }, 3500);
  });

  section.addEventListener("click", function (e) {
    const slide = e.target.closest(".slide");
    if (slide) {
      const slideID = Number(slide.dataset.slide);

      goToSlide(slideID, slide.closest(".slider"));
      showImage(slideID, slide.closest(".slider"));
    }
  });
};

//////////////////////////////////Admins & NavTabs/////////////////////
// Home Admin
const homeAdmin = function () {
  homePage.style.display = "block";
  navbarManipulation("home");
};

// Gallery Admin
const galleryAdmin = function () {
  galleryPage.style.display = "block";

  fetch(`request_gallery`)
    .then((response) => response.json())
    .then((images) => {
      renderImages(images);
      gallerySlider();
    });
};

// Blog Admin
const blogAdmin = function () {
  blogPage.style.display = "block";

  // Getting all the article categories
  fetch("/request_category")
    .then((response) => response.json())
    .then((categoryArray) => {
      // Insert articles according to saved global articles and current page
      if (activeCategoryID) requestArticles(activeCategoryID);
      else requestArticles(categoryArray[0].id);

      // Creating links according to article categories
      createCategoryLinks(categoryArray);

      // Listen on viewport size changes
      window.matchMedia(smMediaQuery).addEventListener("change", function () {
        createCategoryLinks(categoryArray);
      });
    });
};

// Show Page that's Clicked
const showPage = function (page) {
  navbarManipulation(page);

  document.querySelectorAll(".webpage").forEach((page) => (page.style.display = "none"));

  // Remove HTML whenever leaving gallery page
  document.querySelector(".gallery-section").innerHTML = "";

  if (page == "home") homeAdmin();
  if (page == "blog") blogAdmin();
  if (page == "gallery") galleryAdmin();

  window.scrollTo(0, 0);
};

// Initialisation
const init = function () {
  homeAdmin();

  // ***Navbar Events***
  // Navbar Tabs
  navbars.forEach((nav) => {
    nav.addEventListener("click", (e) => {
      if (e.target.classList.contains("homenav-link") || e.target.classList.contains("nav-link")) showPage(e.target.dataset.page);
    });
  });

  // Navbar Fade Animation
  layoutNav.addEventListener("mouseover", handleHover.bind(0.5));
  layoutNav.addEventListener("mouseout", handleHover.bind(1));

  // ***Home Admin***
  // Swapping Text & Image Column
  swap.call(window.matchMedia(mdMediaQuery));
  window.matchMedia(mdMediaQuery).addEventListener("change", swap);

  // Reveal Section
  allSections.forEach((section) => {
    section.classList.add("section--hidden");
    sectionObserver.observe(section);
  });

  // Explore links
  document.querySelector(".category_cards-container").addEventListener("click", (e) => {
    if (e.target.classList.contains("explore-link")) {
      showPage("blog");
      requestArticles(e.target.dataset.category);
    }
  });

  // Implement Home Slider
  slider();

  // Listen to prefooter btn
  document.querySelector(".pre-footer-btn").addEventListener("click", () => {
    showPage("blog");
  });

  // ***Blog Events***
  // Listen on pagination links
  document.querySelector(".pagination").addEventListener("click", function (e) {
    if (e.target.closest(".working-page-link")) {
      insertArticles(globalArticles, e.target.closest(".working-page-link").dataset.pg);
    }
  });

  linksContainer.addEventListener("click", (e) => {
    const category = e.target.dataset.category;
    if (category) {
      requestArticles(category);
    }
  });
  dropdownMenu.addEventListener("click", (e) => {
    const category = e.target.dataset.category;
    if (category) {
      requestArticles(category);
    }
  });
  articleContainer.addEventListener("click", readArticle);
};
init();
