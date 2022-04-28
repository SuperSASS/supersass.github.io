(()=>{var p={strongEaseOut:function(r,e,t,s){return t*((r=r/s-1)*r*r*r*r+1)+e},linear:function(r,e,t,s){return t*r/s+e}},h=function(r){this.dom=r,this.startTime=0,this.startPos=0,this.endPos=0,this.easing=null,this.duration=null},c=0;h.prototype.start=function(r,e,t){this.startTime=+new Date,this.startPos=this.dom.scrollTop,this.endPos=r,this.duration=e,this.easing=p[t];var s=this,i=setInterval(function(){(s.step()===!1||i<c)&&clearInterval(i)},10);c=c<i?i:c};h.prototype.step=function(){var r=+new Date;if(r>=this.startTime+this.duration)return this.update(this.endPos),!1;var e=this.easing(r-this.startTime,this.startPos,this.endPos-this.startPos,this.duration);this.update(e)};h.prototype.update=function(r){this.dom.scrollTop=r};var u=h;var y=class{otherList=new Array;classTOC;TOC;content;currentTOC;constructor(e){this.getOtherList(document.getElementById("main-menu")),this.classTOC=document.getElementsByClassName("sticky-toc")[0],this.TOC=document.getElementById("TableOfContents"),this.content=e.getElementsByTagName("span")[0],this.currentTOC="disappear",this.bindClick(e),window.addEventListener("DOMContentLoaded",()=>{this.enableStickyToc()}),this.TOC.style.setProperty("transition","all .3s ease"),e.style.setProperty("transition","all .3s ease")}bindClick(e){e.addEventListener("click",t=>{this.currentTOC=="show"?(this.changeDisplay("show"),this.content.innerHTML="\u663E\u793A\u6587\u7AE0\u76EE\u5F55",this.currentTOC="disappear"):(this.changeDisplay("disappear"),this.content.innerHTML="\u9690\u85CF\u6587\u7AE0\u76EE\u5F55",this.updatePosAndColor(),this.currentTOC="show")})}enableStickyToc(){let e=new IntersectionObserver(i=>{i.forEach(n=>{let l=n.target.getAttribute("id");if(n.isIntersecting){if(t==!0){let a=document.querySelector(".sticky-toc li.active");a.firstChild.classList.remove(s),a.classList.remove("active"),t=!1,this.updatePosAndColor()}let o=document.querySelector(`.sticky-toc li a[href="#${l}"]`);o&&(o.parentElement.classList.add("active"),this.updatePosAndColor())}else if(document.querySelectorAll(".sticky-toc li.active").length==1)t=!0;else{let o=document.querySelector(`.sticky-toc li a[href="#${l}"]`);o&&(o.classList.remove(s),o.parentElement.classList.remove("active"),this.updatePosAndColor())}})});var t=!1,s="text-now";document.querySelectorAll(".article-content h1[id]").forEach(i=>{e.observe(i)}),document.querySelectorAll(".article-content h2[id]").forEach(i=>{e.observe(i)}),document.querySelectorAll(".article-content h3[id]").forEach(i=>{e.observe(i)}),document.querySelectorAll(".article-content h4[id]").forEach(i=>{e.observe(i)}),document.querySelectorAll(".article-content h5[id]").forEach(i=>{e.observe(i)}),document.querySelectorAll(".article-content h6[id]").forEach(i=>{e.observe(i)})}updatePosAndColor(){var e="text-now",t=document.querySelector("#sticky-toc"),s=new u(t);let i=document.querySelectorAll(".sticky-toc li.active"),n=i.length;if(n!=0){let o=i[0];o.firstChild.classList.add(e);var l=window.innerHeight*.3;let a=o.offsetTop-l;a>0?s.start(a,300,"linear"):s.start(0,300,"linear");for(let d=1;d<n;d++)i[d].firstChild.classList.remove(e)}}changeDisplay(e){for(let t=0;t<this.otherList.length;t++)e=="disappear"?(this.otherList[t].style.height=0,this.otherList[t].style.padding=0,this.otherList[t].style.margin=0,this.otherList[t].style.visibility="hidden",this.otherList[t].style.opacity=0,this.TOC.style.visibility="visible",this.TOC.style.opacity=1,this.classTOC.style.setProperty("overflow-y","auto")):(this.otherList[t].style.height="auto",this.otherList[t].style.padding="",this.otherList[t].style.margin="",this.otherList[t].style.visibility="visible",this.otherList[t].style.opacity=1,this.TOC.style.visibility="hidden",this.TOC.style.opacity=0,this.classTOC.style.setProperty("overflow-y","hidden"))}getOtherList(e){let t=e.getElementsByTagName("li");for(let s=0;s<t.length;s++)if(t[s].id=="basic"){this.otherList.push(t[s]);let i="height "+String((s+1)*.15)+"s ease,padding "+String((s+1)*.15)+"s ease,margin "+String((s+1)*.15)+"s ease,visibility "+String(s*.1)+"s ease,opacity "+String(s*.1)+"s ease";t[s].style.setProperty("transition",i)}}};document.getElementById("toc-button")&&new y(document.getElementById("toc-button"));})();
