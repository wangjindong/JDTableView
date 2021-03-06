# JDTableView

>iOS项目用的最多的控件中tableview恐怕是有着举足轻重位置，可是你如果还在自己实现tableview的delegate和datasource恐怕就low了，尤其是delegate和datasource逻辑大同小异，而本项目就是针对一个数组来抽象实现掉delegate和datasource，甚至完全靠一个数组源都能全部处理掉tableview的渲染和事件处理。

这种写法也能帮开发者只关注数据和界面，不需要考虑tableview的渲染逻辑

对tableview的拓展，利用runtime的class_addMethod向delegate和dataSource动态添加实现协议方法，不用实现一个方法即可展示数据，因为动态添加前会判断delegate和dataSource里面是否已有该方法，所以你可以根据自己的喜好来先行实现！

此效果图的实现可看代码，极其简单，不用实现一行协议代码

![](https://github.com/wangjindong/JDTableView/blob/master/tableview.gif)



设计理念：动态添加委托方法，实现tableview的委托，不需要程序猿实现任何接口方法，所有可能来源均有数据结构（即数组）提供！

该方法支持在数据里面增加tableview的选择事件，默认的cell样式、accessoryView,block等等！

## 使用就四步

 >第一步 设置委托类： self.tableView.jd_delegate = self;
 
 >第二步 设置数据源： self.tableView.jd_dataSource = self;
 
 >第三步 作配置表，比如配置cell的数组，数据对应的cell数组的索引。

 >第四步 构造数据源，将它处取得数据交由JDViewModel来管理。

如：

```
- (void)viewDidLoad {
    [super viewDidLoad];
    //第一步：设置委托类
    self.tableView.jd_delegate = self;
    //第二步：设置数据源
    self.tableView.jd_dataSource = self;
    //第三步：配置tableView
    [self configTableView];
    //第四部：加工数据源
    [self configDataSource];
  }
 
 
  - (void)configTableView {
    JDTableViewConfig *config = [[JDTableViewConfig alloc] init];
    config.tableViewCellArray = @[[UINib nibWithNibName:@"DemoTableViewCell1" bundle:nil],
                                  [UINib nibWithNibName:@"DemoTableViewCell2" bundle:nil]
                                ];
   //配置数据源与cell的对应关系
    config.cellTypeBlock = ^NSInteger(NSIndexPath *indexPath, id dataInfo) {
        return 0;
    };
    
    //配置都有哪些header
    config.tableViewHeaderViewArray = @[[FirstTableViewHeaderFooterView class]];
    //配置数据源与header的对应关系
    config.headerTypeBlock = ^NSInteger(NSUInteger section, id sectionInfo) {
        return 0;
    };
    
    ////////////////////////编辑////////////////////////
    config.canEditable = ^BOOL(NSIndexPath *indexPath) {
        return YES;
    };

    config.singleLineDeleteAction = ^(NSIndexPath *indexPath) {
        NSLog(@"我要删除第%ld行",indexPath.row);
    };
    self.tableView.jd_config = config;
  }

  - (void)configDataSource {
    self.tableViewModel = [[JDViewModel alloc] init];
    self.tableView.jd_viewModel = self.tableViewModel;
    
    for (NSInteger i = 0; i < 4; i++) {
        //开始组织对象
        JDSectionModel *section = [[JDSectionModel alloc] init];
        //section1.title = @"TableView";
        section.sectionData = [NSString stringWithFormat:@"我是自定义数据%ld",i];
        //section也可以配置数据源与cell的对应关系，它的优先级高于config的配置
        section.cellTypeBlock = ^NSInteger(NSIndexPath *indexPath, id dataInfo) {
            return [dataInfo[@"type"] integerValue];
        };
        NSDictionary *data = [DataUtils dataFromJsonFile:@"first.json"];
        [section addRowDatasFromArray:data[@"items"]];
        [self.tableViewModel addSectionData:section];
    }
  }
```
如果你有好的建议请联系我:419591321@qq.com,其实自己仔细琢磨更有意思！

 
# CocoaPods

1、在 Podfile 中添加 `pod 'JDTableView'`。

2、执行 `pod install` 或 `pod update`。

3、导入 \<JDTableView/JDTableView.h\>。
