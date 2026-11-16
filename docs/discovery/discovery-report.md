# Discovery report

## Problem statement

A renowned film studio in Los Angeles needs a reliable, extensible and cost-effective CPU-based ray tracer to replace Maya in its rendering workflow, because its current licensing costs exceeded $2 million last year, the commercial solution limits the addition of custom features, and unexplained black artefacts previously doubled rendering times.

## Client interview summary

### Production deadline and target film

**Need:** The client needs the new renderer to be ready for production by 5 January 2027 and to support the rendering of a 90-minute film.

> **Q (Development team):** "What is the expected deadline for putting the ray tracer into production?"
>
> **A:** "January 5th, 2027."
>
> **Q (Development team):** "What is the size of the target? How long is the film?"
>
> **A:** "It is a 90-minute film at '8 feet'."

**My conclusion:** The target production date is 5 January 2027, and the renderer must support a feature film lasting 90 minutes. The frame rate was not reliably captured. It must be confirmed before calculating the total number of frames and estimating the required rendering throughput. The expression "8 feet" must not be interpreted as a frame rate or resolution without confirmation.

### Existing solution, limitations and licensing costs

**Need:** The client needs to replace the expensive Maya-based rendering workflow with a more cost-effective solution that can be maintained internally and extended with project-specific features.

> **Q (Development team):** "What did you use for rendering before, what do you use today, and why are you considering a replacement?"
>
> **A:** "We previously had an in-house solution, but it had bugs. We then moved to a commercial solution, Maya. It is very expensive and does not cover all the needs we have for our future projects. On our last project, we made a loss because the licences were so expensive that we could not afford them. We also had to sacrifice some features."
>
> **Q (Development team):** "Are you using a reference solution currently available on the market?"
>
> **A:** "Yes, but it is very expensive, and it does not cover all the needs we have for our future projects."
>
> **Q (Development team):** "What is the main purpose of the new software, beyond rendering images?"
>
> **A:** "We want to render images and be able to add our own features. With Maya, if we want to add something specific, we have to go through a vendor request channel. They either say no, or it takes six months to a year to add the feature. This limits our creativity to what Maya offers."
>
> **Q (Development team):** "What did you spend on rendering licences last year?"
>
> **A:** "We spent more than $2 million on licences. The licence is seat-based: we pay per machine, per artist, and for every single node in our render farm, each with its own licence. That is why the budget is huge. We would like to bring it in-house and save much more."

**My conclusion:** The client previously used an in-house rendering solution but moved to Maya because the internal solution contained bugs. The commercial solution then created significant recurring licensing costs and did not provide enough flexibility for future projects. The new product is intended to replace Maya in the **rendering workflow**. The interview does not establish that the studio wants to replace every Maya capability, such as modelling or animation. In fact, the scene-creation workflow described later relies on a separate third-party tool. The project should therefore focus on replacing the rendering stage unless the client confirms a broader scope.

The client also wants to develop and maintain custom features without depending on a vendor request process that can take six to twelve months or be rejected. The reported licence expenditure of more than $2 million last year makes total cost of ownership a major project driver. The exact renderer or plug-in currently used with Maya has not been identified.

### Scene input, rendering process and image output

**Need:** The renderer must accept a scene file created by the studio's existing third-party software, process it without requiring a graphical interface at the rendering stage, and save the resulting images in PNG format at Full HD resolution.

> **Q (Development team):** "Do you need an interface to connect to the software, or is a file enough?"
>
> **A:** "Typically, a standard file is created and saved by another tool. This file is put onto the render farm, and a process is launched to render the input. No interface is needed at this point."
>
> **Q (Development team):** "How will the scenes and images flow through the process?"
>
> **A:** "The designer uses third-party software to position the objects in the scene and set up the lighting. They save a file, and that file is the input to your renderer, which renders the final image. The images are then saved and either sequenced into a film or viewed one by one."
>
> **Q (Development team):** "Which image format do you expect the renderer to support?"
>
> **A:** "PNG."
>
> **Q (Development team):** "What image resolution do you expect?"
>
> **A:** "Full HD, 1920 × 1080 pixels."

**My conclusion:** The input to the ray tracer is a **3D scene file**, not a pre-existing 2D image. A separate application is responsible for scene preparation, including object placement and lighting. The renderer must load that scene file, execute the rendering process and save the resulting image. The client does not currently require a graphical user interface for this stage; a file-driven, non-interactive or batch workflow is expected.

The final image format is PNG, and the stated Full HD resolution is 1920 × 1080 pixels. The exact scene-file format and the interface used to launch and monitor rendering jobs remain to be defined. The report treats 1920 × 1080 as the final output resolution; the resolution and format of preview images still need confirmation.

### Hardware, previews and rendering performance

**Need:** The renderer must provide quick, lower-resolution previews for designers and high-quality final rendering on the studio's CPU-based production infrastructure. The final rendering phase for the film should not exceed two months.

> **Q (Development team):** "What kind of hardware do you have in your company?"
>
> **A:** "There are three levels. The first is the designer, for the graphics. They have a pretty powerful desktop machine, and the most important thing for them is being able to visualise what they are working on. In this case, you can expect a smaller image, so they get a preview of what they are doing. On the other side, there is the actual production renderer, which is a larger machine with reasonable specifications. We do not have graphics cards, so everything must be rendered by the CPU."
>
> *The answer mentions three levels but only describes designer workstations and production-rendering machines. The third level was not captured in the notes.*
>
> **Q (Development team):** "How long can final rendering take?"
>
> **A:** "Typically, once the creative side is done, we do not want to spend more than two months on final rendering."
>
> **Q (Development team):** "How important are preview speed and final image quality?"
>
> **A:** "For designers, a fast preview is very important. We do not want them to wait too long to see the result of their work. For the final scene, high image quality is very important."
>
> **Q (Development team):** "How many creative renders do you do?"
>
> **A:** "Typically, at least ten different pre-renders per image. The average workflow is about ten pre-renders per image before the final render."

**My conclusion:** The workflow has at least two distinct rendering contexts:

- **Design preview:** Designers use powerful desktop workstations and need fast visual feedback. Smaller preview images are acceptable because speed is more important than final image quality at this stage.
- **Final production rendering:** Final images are rendered on larger production machines and/or the render farm. The client has no GPUs available, so the production renderer must support CPU-only rendering.

The renderer must support repeated preview renders and high-quality final renders. The client typically performs around ten pre-renders per image before the final render. The final rendering phase for the 90-minute film should take no more than two months once creative work is complete. However, the number of render-farm nodes, CPU specifications, preview response time and exact frame rate are unknown. The two-month target cannot yet be translated into a reliable per-frame rendering budget.

### Rendering reliability and diagnosis

**Need:** The client needs reproducible rendering results and the ability to identify the cause of an image anomaly and determine corrective actions within the same working day.

> **Q (Development team):** "What problems demonstrate that the current rendering solution does not meet your needs?"
>
> **A:** "The current rendering tools produce artefacts, pixel-related problems and rendering errors. Nobody on the team can explain why these problems occur."
>
> **Q (Development team):** "When was the last time a rendering process failed, and what happened?"
>
> **A:** "Six months ago. We had a major project that was about to be published, and we kept finding black artefacts in the images. The rendering time also doubled. We asked the team why there were black dots in the images, but nobody could explain what was happening or identify the problem."
>
> **Q (Development team):** "What will show you that the new software meets your needs?"
>
> **A:** "There are two elements. First, it produces a reliable image: if I give it some inputs, I can always expect the same output. Second, if there is an anomaly in an image, we can work out within the same day why it happened and what steps we can take to correct it. This goes back to the problem we had six months ago. We had black spots everywhere and nobody could tell us why. That was our biggest frustration."

**My conclusion:** The main reliability issue is not limited to visual quality. The studio also needs to understand why a rendering result is wrong. Six months before the interview, a production project was affected by black artefacts and a rendering time that doubled; the team could not identify the root cause. The new renderer should therefore be designed around two explicit acceptance expectations:

1. **Reproducibility:** The same scene and rendering configuration should produce the same expected output. The technical meaning of "the same output" (visually identical or pixel-for-pixel identical) should be clarified.
2. **Diagnosability:** When an anomaly occurs, the team should be able to identify its cause and the corrective steps within the same working day.

Automated regression tests, structured logs, diagnostic information, documented rendering settings and reproducible test scenes are relevant engineering measures. They should help prevent regressions and make failures explainable rather than merely detecting that an image is wrong.

### Maintenance, open-source policy and partner contributions

**Need:** The client wants to maintain the software internally, automate relevant processes, keep the code open source and allow partner studios to contribute changes through a controlled process while the client retains responsibility for the software.

> **Q (Development team):** "How do you intend to maintain the solution?"
>
> **A:** "We want to maintain it in-house and automate the process."
>
> **Q (Development team):** "Should all the code be open source, or do you need some parts to stay in-house so you keep control of the software?"
>
> **A:** "Currently, everything is open source."
>
> **Q (Development team):** "Do your partner studios take part, and would they contribute to this tool?"
>
> **A:** "We rely on partners to do the rendering for us, and these partners have the skill sets to contribute to this project as well. We will keep responsibility for the software, but we would like a way for them to contribute their changes correctly."

**My conclusion:** The client expects an open-source approach and wants to retain internal responsibility for the product. Partner studios are both users of the rendering workflow and potential contributors. The project therefore needs clear contribution rules, coding standards, documentation, automated checks, code review and an explicit release process. The client should remain responsible for approving and integrating contributions. The exact open-source licence and the governance roles still need to be selected.

### Budget

**Need:** The client wants to cap the investment in the new solution at 500,000, with the expectation that the actual investment should be lower than this ceiling.

> **Q (Development team):** "What is your budget?"
>
> **A:** "We would like to spend no more than 500,000. Last year's budget was 2 million, so this is one quarter. We can use that to run the development team we hire, but we expect the investment to be cheaper."

**My conclusion:** The client has set a maximum budget of 500,000 and expects the project to cost less. The notes do not explicitly record the currency, nor do they establish whether the ceiling includes only the development team or also infrastructure, hardware, support and operation. These points must be confirmed before creating a realistic cost estimate. The stated ceiling is approximately one quarter of the previous year's 2-million budget, according to the client.

### Open questions

- **Scope of Maya replacement:** Can the client confirm that the new software is expected to replace Maya's role in the rendering workflow, while scene creation remains in the existing third-party application? Is any modelling, animation or scene-authoring functionality also expected?
- **Current rendering stack:** Which renderer or plug-in is currently used with Maya? The interview identifies Maya but does not identify the rendering engine or its version.
- **Job execution:** How should the render process be launched and monitored on the render farm (command-line interface, job scheduler, API or another mechanism)? The client said no graphical interface is needed at the rendering stage, but the operational interface is not yet defined.
- **Performance targets:** What is the maximum acceptable wait for a designer preview? What quality settings are expected for previews and final renders? Does the two-month limit apply to rendering the entire 90-minute film on the existing render farm?
- **Open-source governance:** Which licence should be used? Who will review and approve partner contributions? What contribution, testing, security and release policies are expected?
- **Maintenance continuity:** What happens if the person responsible for maintaining the software leaves the team? How should knowledge transfer and long-term project ownership be organised?&#x20;

## State of the art

The comparison below focuses on solutions relevant to professional rendering. Maya is a broader 3D creation application, while RenderMan and Cycles are rendering engines. This distinction matters because the client wants to replace Maya in the rendering workflow, but the interview indicates that scene creation will continue in a separate third-party tool.

| Solution                                                                                                          | Maker                               | Licence                                                                             | Pricing (date checked: 16 November 2026)                                                                                                                                                                                                                        | Capabilities                                                                                                                                                                                                                                                                                        | Sources                                                                                                                                                                                                                                       |
| ----------------------------------------------------------------------------------------------------------------- | ----------------------------------- | ----------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Autodesk Maya (with Arnold as a relevant Autodesk rendering option; the client's exact renderer is not confirmed) | Autodesk                            | Proprietary commercial subscription                                                 | Maya: €2,112/year. Arnold: €450/year when subscribed separately. The Media & Entertainment Collection is listed at €2,934/year and includes Maya, 3ds Max, Arnold and other tools. Autodesk indicates estimated VAT is included in the displayed French prices. | Full 3D application covering modelling, animation, simulation and rendering. Arnold is Autodesk's global-illumination renderer. Autodesk's render-farm guidance states that an Arnold render licence is required for each machine rendering simultaneously.                                         | [Autodesk France pricing](https://www.autodesk.com/fr/products) · [Autodesk Arnold render-farm licensing](https://www.autodesk.com/support/technical/article/caas/sfdcarticles/sfdcarticles/How-to-set-up-an-Arnold-Render-Farm.html)         |
| Pixar RenderMan 27                                                                                                | Pixar Animation Studios             | Proprietary commercial licence; non-commercial version available for eligible users | $595 USD per commercial licence, plus $250 USD annual maintenance per licence. Enterprise configurations can require a quote.                                                                                                                                   | Production renderer with physically based rendering, path tracing, multi-threading, custom integrators and materials through APIs. Licences can be floating or node-locked; one licence can be used for an artist seat or batch rendering. CPU rendering is supported on compatible AVX processors. | [RenderMan pricing and licensing](https://prod.renderman.pixar.com/store) · [RenderMan technical specifications](https://renderman.pixar.com/product/tech-specs)                                                                              |
| Blender with Cycles                                                                                               | Blender Foundation and contributors | Blender: GNU GPL v2 or later. Cycles: Apache License 2.0.                           | Free to use; no software subscription fee.                                                                                                                                                                                                                      | Blender is a complete 3D creation suite. Cycles is its path-tracing renderer and supports both CPU and GPU rendering. The Blender manual states that CPU rendering supports all Cycles features.                                                                                                    | [Blender licence](https://www.blender.org/about/license/) · [Cycles licence](https://github.com/blender/cycles/blob/main/LICENSE) · [Cycles render settings](https://docs.blender.org/manual/en/5.0/render/cycles/render_settings/index.html) |

*Prices are public list prices checked on 16 November 2026. They are not directly comparable to the client's enterprise agreement or actual number of artist seats and render-farm nodes. The interview reports more than $2 million spent on licences last year; the public prices above only provide market reference points.*

**My conclusion:**

The comparison shows that established commercial products already provide professional rendering capabilities, but their licensing models can become expensive when licences are required for artists and render-farm machines. Autodesk's public pricing confirms that Maya and Arnold are separately listed products, while Autodesk's render-farm guidance describes a per-machine Arnold licence requirement for simultaneous rendering. Pixar RenderMan also uses commercial licensing, although its floating-licence option offers flexibility across a network.

Blender with Cycles is an important open-source reference because it supports CPU rendering and does not require a software subscription. Its existence means that the project should explain why a dedicated C++ ray tracer is preferable to adopting or adapting an existing open-source renderer.

Based on the interview, the strongest reasons to investigate a custom renderer are not simply to remove licence fees. The client also wants reproducible outputs, same-day diagnosis of rendering anomalies, control over feature development, an automated file-based render-farm workflow and a contribution process for partner studios. The new renderer must be benchmarked on the client's actual CPU hardware and representative scene files. Development, hardware, integration and maintenance costs must also be included when comparing total cost of ownership.

## What is ray tracing?

Ray tracing is a computer graphics technique that generates a two-dimensional image from a three-dimensional scene by simulating how light interacts with objects. The input is a scene containing geometry, materials, lights and a camera. For each pixel, the renderer sends one or more rays from the camera into the scene and calculates where they intersect objects. It then evaluates the material and lighting at those intersections to determine the pixel's colour. Additional rays can simulate shadows, reflections, refractions and indirect lighting. Repeating these calculations for all pixels produces the final image. The quality and rendering time depend on the scene complexity, resolution, number of samples, light interactions and available computing resources. In this project, the renderer will receive a scene file created by another application and produce image files, with PNG and 1920 × 1080 pixels identified as the client's current final-output requirements. The production hardware is CPU-only, so the implementation must be designed and benchmarked for CPU rendering.

**Sources:**

- **What we started from:** [How to research this project](https://learn.glassworks.tech/raytracer/veille-perspective/how-to-research/), the course guide explaining desk research, client interviews, competitive analysis and the need to turn vague performance requirements into measurable questions.
- **Learning resource:** [Ray Tracing in One Weekend](https://raytracing.github.io/), a practical C++ tutorial series that builds a ray tracer step by step, covering rays, geometry, materials, lighting and rendering.
- **Technical reference:** [Physically Based Rendering: From Theory to Implementation, 4th Edition](https://www.pbr-book.org/4ed/), a detailed reference on rendering algorithms and physically based rendering.

## What is C++?

C++ is a general-purpose, statically typed, compiled programming language used in performance-sensitive software such as graphics engines, simulations and rendering systems. It offers high-level abstractions while also providing control over memory, object lifetimes, data representation and CPU execution. This makes it suitable for a ray tracer that must process large numbers of ray-object intersections, operate on CPU-only render-farm machines and remain maintainable over several years. C++ does not guarantee performance or safety automatically: the quality of the algorithms, data structures, memory management, concurrency design and testing practices remains essential.

### Programming paradigms

C++ is a multi-paradigm language. Several programming approaches can be combined according to the responsibilities of the application:

- **Procedural programming:** Organises instructions into functions and sequences of operations. It is useful for mathematical calculations, ray traversal and rendering steps.
- **Object-oriented programming (OOP):** Organises code around objects that combine data and behaviour. Encapsulation, abstraction, inheritance and polymorphism can represent concepts such as cameras, geometries, materials and lights.
- **Generic programming:** Uses templates to write reusable algorithms and data structures that work with different types. It can be useful for vectors, matrices, colours and mathematical operations.
- **Functional programming techniques:** Uses functions, lambdas and standard algorithms to organise computations. These techniques can help isolate calculations and limit shared mutable state, which is particularly useful in concurrent rendering code.

Compared with Java, C++ gives developers more direct control over memory allocation and object lifetimes. Java relies on automatic garbage collection, whereas modern C++ commonly uses RAII and smart pointers to manage resources. Compared with Python, C++ is statically typed and normally compiled to native machine code, offering greater control over data layout and execution. Python can still be useful for tooling and automation, but the rendering core is required to be written in C++.

For this project, object-oriented design can structure the domain concepts, while procedural and generic programming can support the mathematical and performance-sensitive parts. The team should select each paradigm where it improves clarity or efficiency rather than introducing abstractions without a clear purpose.

### What to watch out for

C++ provides control over system resources, but that control introduces engineering responsibilities:

- **Memory management:** Developers must manage resource ownership and object lifetimes. Incorrect handling can cause memory leaks, double deletion and invalid memory access.
- **Pointers and references:** They provide access to objects without necessarily copying them, but dangling pointers and references can cause undefined behaviour.
- **Undefined behaviour:** Errors such as out-of-bounds access, use of uninitialised values or invalid object access can produce unpredictable results.
- **Resource management:** RAII (Resource Acquisition Is Initialization) ties resource lifetime to object lifetime. `std::unique_ptr`, `std::shared_ptr` and standard containers help make ownership explicit and reduce manual memory-management errors.
- **Concurrency:** CPU rendering can be parallelised across threads and render-farm machines. Shared mutable data can introduce data races, deadlocks and inconsistent results, so concurrency boundaries and ownership must be designed carefully.
- **Determinism:** The client expects the same inputs to produce the same output. Sampling algorithms, random seeds, thread scheduling and floating-point operations must be considered when defining the required level of reproducibility.
- **Performance optimisation:** Efficient rendering depends on suitable algorithms, data structures, memory access patterns and profiling. Performance should be measured on the studio's real CPU hardware rather than assumed from isolated tests.
- **Code quality and AI-generated code:** Complex C++ can be difficult to maintain. Code reviews, automated tests, static analysis, documented design decisions and careful review of generated code are necessary to prevent unexplainable behaviour from entering the codebase.

For this project, modern C++ practices should be preferred. Resource ownership should be explicit, avoidable allocations should be reduced, concurrency should be tested, and errors should be diagnosable. The codebase must remain understandable to the internal team and contributing partner studios.

### Shaping the domain model

The domain model should represent the concepts required to transform a scene file into a rendered image. The following is a first proposal based on the interview; the exact input format and supported scene features still need to be confirmed.

| Component         | Responsibility                                                                                                                                               |
| ----------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `SceneFileLoader` | Reads and validates the standard scene file produced by the third-party authoring tool. Its implementation will depend on the format selected by the client. |
| `Scene`           | Holds the geometries, materials, lights and camera that define the 3D environment.                                                                           |
| `Camera`          | Defines the viewpoint and generates rays directed into the scene.                                                                                            |
| `Ray`             | Represents a ray using an origin and a direction in 3D space.                                                                                                |
| `Geometry`        | Represents objects that rays can intersect, such as spheres, planes and triangles.                                                                           |
| `Material`        | Defines how a surface interacts with incoming light.                                                                                                         |
| `Light`           | Represents light sources and their contribution to the scene.                                                                                                |
| `Intersection`    | Stores information about where a ray hits an object, including position, surface normal and distance.                                                        |
| `RenderSettings`  | Defines resolution, sampling, quality and other rendering parameters for preview or final output.                                                            |
| `Renderer`        | Coordinates ray generation, intersection testing, light calculations and image production on the CPU.                                                        |
| `RenderJob`       | Represents a non-interactive rendering task, including its input scene, settings, output destination and diagnostic information.                             |
| `ImageBuffer`     | Stores the resulting pixel data in memory.                                                                                                                   |
| `PngWriter`       | Exports the rendered image as a PNG file.                                                                                                                    |

The architecture should keep scene-file parsing, rendering calculations, job execution and image export separate. This will allow the renderer to support the client's existing scene workflow without coupling the rendering core to a particular authoring application.

**Encapsulation** should ensure that each component manages its own data and exposes only the operations required by other components. **Abstraction** can define common contracts for geometry and material behaviours. **Polymorphism** can allow the renderer to process different geometry and material types through common interfaces. **Composition** should be preferred when assembling scenes from independent objects and services; inheritance should be used only where a meaningful relationship exists.

C++ ownership rules should be reflected in the model. A scene may own its geometries and other long-lived objects through standard-library containers and smart pointers, while lightweight mathematical structures such as vectors, points and colours can be implemented as value types.

The rendering process should distinguish at least two configurations:

- **Preview rendering:** prioritises speed and can use a smaller resolution or lower sampling quality to give designers rapid visual feedback.
- **Final rendering:** prioritises image quality and produces the required PNG output at 1920 × 1080 pixels, using CPU resources available on the production infrastructure.

The renderer should also expose a non-interactive job execution path suitable for the render farm. The job should record its input, settings, output location and diagnostic details so that the team can reproduce and investigate anomalies. The exact mechanism for distributing jobs across render-farm nodes remains an infrastructure decision.

Finally, SOLID and DRY should guide the design without creating unnecessary abstractions. Components should have clear responsibilities, limited dependencies and automated tests wherever possible. This will make the renderer easier to understand, maintain and extend internally and through partner contributions.

**Sources:**

- **What we started from:** [How to research this project](https://learn.glassworks.tech/raytracer/veille-perspective/how-to-research/), which recommends finding both an introductory C++ resource and a technical reference.
- **Learning resource:** [LearnCpp.com](https://www.learncpp.com/), a tutorial covering modern C++, object-oriented programming, templates, pointers, smart pointers and debugging.
- **Technical reference:** [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines), which provides guidance on resource management, memory safety, interfaces and modern C++ design.
- **Additional reference:** [cppreference](https://en.cppreference.com/), a detailed reference for the C++ language and standard library.
