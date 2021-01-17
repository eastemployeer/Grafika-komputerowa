//PROJECT
import * as THREE from '/build/three.module.js';
import { OrbitControls } from '/jsm/controls/OrbitControls';
import { DragControls } from '/jsm/controls/DragControls';
import { FBXLoader } from '/jsm/loaders/FBXLoader';
import Stats from '/jsm/libs/stats.module';
import { TWEEN } from '/jsm/libs/tween.module.min';
const scene = new THREE.Scene();
var light = new THREE.AmbientLight();
scene.add(light);
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.01, 1000);
camera.position.set(0.8, 1.4, 1.0);
const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.shadowMap.enabled = true;
document.body.appendChild(renderer.domElement);
const controls = new OrbitControls(camera, renderer.domElement);
controls.screenSpacePanning = true;
controls.target.set(0, 1, 0);
let sceneMeshes = new Array();
//GROUND AND GROUND TEXTURE
const planeGeometry = new THREE.PlaneGeometry(100, 100);
const texture = new THREE.TextureLoader().load("img/snow-texture-background.jpeg");
const plane = new THREE.Mesh(planeGeometry, new THREE.MeshPhongMaterial({ map: texture }));
plane.rotateX(-Math.PI / 2);
plane.receiveShadow = true;
scene.add(plane);
sceneMeshes.push(plane);
let mixer;
let modelReady = false;
let modelMesh;
let animationActions = new Array();
let activeAction;
let lastAction;
//OBJECT LOADING
const fbxLoader = new FBXLoader();
fbxLoader.load('models/aj.fbx', (fbx) => {
    fbx.traverse(function (child) {
        if (child.isMesh) {
            let m = child;
            m.castShadow = true;
            m.frustumCulled = false;
            m.geometry.computeVertexNormals();
        }
    });
    fbx.scale.set(0.01, 0.01, 0.01);
    mixer = new THREE.AnimationMixer(fbx);
    let animationAction = mixer.clipAction(fbx.animations[0]);
    animationActions.push(animationAction);
    activeAction = animationActions[0];
    scene.add(fbx);
    modelMesh = fbx;
    fbxLoader.load('models/aj@stop.fbx', (fbx) => {
        console.log("loaded stop");
        let animationAction = mixer.clipAction(fbx.animations[0]);
        animationActions.push(animationAction);
        fbxLoader.load('models/aj@running.fbx', (fbx) => {
            console.log("loaded running");
            fbx.animations[0].tracks.shift(); //delete the specific track that moves the object forward while running
            let animationAction = mixer.clipAction(fbx.animations[0]);
            animationActions.push(animationAction);
            modelReady = true;
        }, (xhr) => {
            console.log((xhr.loaded / xhr.total * 100) + '% loaded');
        }, (error) => {
            console.log(error);
        });
    }, (xhr) => {
        console.log((xhr.loaded / xhr.total * 100) + '% loaded');
    }, (error) => {
        console.log(error);
    });
}, (xhr) => {
    console.log((xhr.loaded / xhr.total * 100) + '% loaded');
}, (error) => {
    console.log(error);
});
window.addEventListener('resize', onWindowResize, false);
function onWindowResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
    render();
}
const raycaster = new THREE.Raycaster();
const targetQuaternion = new THREE.Quaternion();
//DOUBLE CLICK EVENT HANDLER
renderer.domElement.addEventListener('dblclick', onDoubleClick, false);
function onDoubleClick(event) {
    const mouse = {
        x: (event.clientX / renderer.domElement.clientWidth) * 2 - 1,
        y: -(event.clientY / renderer.domElement.clientHeight) * 2 + 1
    };
    raycaster.setFromCamera(mouse, camera);
    const intersects = raycaster.intersectObjects(sceneMeshes, false);
    if (intersects.length > 0) {
        const p = intersects[0].point;
        const distance = modelMesh.position.distanceTo(p); //assume that return is in meters
        //setting matrix which represents all angles of look to the p object from modelMesh.position
        const rotationMatrix = new THREE.Matrix4();
        rotationMatrix.lookAt(p, modelMesh.position, modelMesh.up); // lookat p from modelMesh.position, point upwards
        //Quaternions are used to rotate objects
        targetQuaternion.setFromRotationMatrix(rotationMatrix);
        setAction(animationActions[2]);
        TWEEN.removeAll(); //pozbycie sie dotychczasowych TWEENów - wyeliminowanie problemu 2 nakladajacych sie eventów doubleclick
        new TWEEN.Tween(modelMesh.position)
            .to({
            x: p.x,
            y: p.y,
            z: p.z
        }, 1000 / 2 * distance) /// 1 second for 1 meter. if 500 ms * dist then 1 second is 2 meters
            .onUpdate(() => {
            controls.target.set(modelMesh.position.x, modelMesh.position.y + 1, modelMesh.position.z);
        })
            .start()
            .onComplete(() => {
            setAction(animationActions[1]);
            activeAction.clampWhenFinished = true;
            activeAction.loop = THREE.LoopOnce;
        });
    }
}
const stats = Stats();
document.body.appendChild(stats.dom);
const setAction = (toAction) => {
    if (toAction != activeAction) {
        lastAction = activeAction;
        activeAction = toAction;
        //lastAction.stop()
        lastAction.fadeOut(.2);
        activeAction.reset();
        activeAction.fadeIn(.2);
        activeAction.play();
    }
};
//TEXTURES
let spheres = new Array();
for (let i = 0; i < 100; i++) {
    const geo = new THREE.SphereGeometry();
    const material = new THREE.MeshPhongMaterial({ shininess: 50, reflectivity: 1, refractionRatio: 0.98, color: 0xffffff, emissive: 0x0, specular: 0x898989 });
    switch (i % 3) {
        case 0:
            const texture = new THREE.TextureLoader().load("img/Ornament4_1.jpg");
            //const specularTexture = new THREE.TextureLoader().load("img/Ornament4_2.jpg")
            material.map = texture;
            // material.specularMap = specularTexture;
            break;
        case 1:
            const texture1 = new THREE.TextureLoader().load("img/Ornament5_1.jpg");
            // const specularTexture1 = new THREE.TextureLoader().load("img/Ornament5_2.jpg")
            material.map = texture1;
            // material.specularMap = specularTexture;
            break;
        case 2:
            const texture2 = new THREE.TextureLoader().load("img/Ornament7_1.jpg");
            // const specularTexture2 = new THREE.TextureLoader().load("img/Ornament7_2.jpg")
            material.map = texture2;
            // material.specularMap = specularTexture;
            break;
    }
    const sphere = new THREE.Mesh(geo, material);
    spheres.push(sphere);
}
spheres.forEach((c) => {
    c.position.x = (Math.random() * 100) - 50;
    c.position.z = (Math.random() * 100) - 50;
    c.geometry.computeBoundingBox();
    c.position.y = (c.geometry.boundingBox.max.y - c.geometry.boundingBox.min.y) / 2 + Math.random() * 4;
    scene.add(c);
});
const backGroundTexture = new THREE.CubeTextureLoader().load(["img/px.png", "img/nx.png", "img/py.png", "img/ny.png", "img/pz.png", "img/nz.png"]);
scene.background = backGroundTexture;
//DRAG CONTROLS - possibility to move spheres
const dragControls = new DragControls(spheres, camera, renderer.domElement);
dragControls.addEventListener("hoveron", function () {
    controls.enabled = false;
});
dragControls.addEventListener("hoveroff", function () {
    controls.enabled = true;
});
dragControls.addEventListener('dragstart', function (event) {
    event.object.material.opacity = 0.33;
});
dragControls.addEventListener('dragend', function (event) {
    event.object.material.opacity = 1;
});
const clock = new THREE.Clock();
var animate = function () {
    requestAnimationFrame(animate);
    controls.update();
    if (modelReady) {
        mixer.update(clock.getDelta());
        if (!modelMesh.quaternion.equals(targetQuaternion)) {
            modelMesh.quaternion.rotateTowards(targetQuaternion, clock.getDelta() * 1000);
        }
    }
    TWEEN.update();
    render();
    stats.update();
};
function render() {
    renderer.render(scene, camera);
}
animate();
