高亮通过后处理实现：

1. 场景中加入一个物体：Volumes-Post Process Volume
2. 设置Volume的Details：Infinite Extent(Unbound)开启
3. 设置Volume的Materials： 添加对应Highlight效果材质
4. 在需要高亮的物体的Details中，选择Mesh，设置RenderCustomDepth，以及设置CustomDepth Stencil Value为250（和材质中设置的值对应）


高亮材质说明：
- 需要ProjectSetting的Custom Depth-Stencil Pass 启用Enabled with Stencil.
- 材质蓝图中最开始的1.6是描边宽度，可以根据需要调整